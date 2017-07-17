/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "BaseService.h"
#include "LibCruxdb.h"
#include "SaveUserHelper.h"
#include "LoggerFactory.h"
#include "DateTimeUtils.h"
#include "AuthUtils.h"
#include "PassWordEncoder.h"
#include <Wt/Dbo/WtSqlTraits>
#include <BlockExecutor.h>


namespace Mocxygen {


    void SaveUserHelper::ExecuteHelper() noexcept(false) {
        LOG_DEBUG("Mocxygen input: " + m_input->Serialize().serialize());
        bool createNew = false;


        if (!(m_requester->HasRole(Role::ROLE_CREATE_SUPER_USER) ||
              m_requester->HasRole(Role::ROLE_SYSTEM_ADMIN))) {
            throw Common::AppException(AppErrorCode::INSIFFICIENT_PRIVILEGE, "Insufficient privilege");
        }

        User *user = nullptr;
        Cruxdb::AuthInfo *authInfo = nullptr;
        Cruxdb::AuthIdentity *identity = nullptr;
        auto userService = Cruxdb::GetUserService();
        
        if (m_input->GetId()) {
            createNew = true;
        }

        if (!createNew) {
            if (m_input->GetEmail()) {
                m_user = userService->GetUser(m_requester, *m_input->GetEmail());

                if (m_user) {
                    throw Common::AppException(AppErrorCode::USER_ALREADY_EXISTS,
                                               "User with the email already exists");
                }
            } else {
                return;
            }
        }

        LOG_DEBUG("Registering new user.");

        try {
            BlockExecutor blockExecutor;
            if (createNew) {
                user = new User();
            } else {
                user = m_user.modify();
            }


            blockExecutor.Execute(m_input->GetName() != boost::none, [&]() -> void {
                user->SetName(*(m_input->GetName()));
            });


            blockExecutor.Execute(m_input->GetRoles() != boost::none, [&]() -> void {
                user->SetRolesStr(*(m_input->GetRoles()));
            });


            blockExecutor.Execute(m_input->GetStatus() != boost::none, [&]() -> void {
                user->SetStatusStr(*(m_input->GetStatus()));
            });

            //user->SetVersion(m_input->GetVersion());

            Wt::Dbo::ptr<User> userSaved;

            if (blockExecutor.IsInvoked()) {
                userSaved = userService->SaveEntity(m_requester, user);
            }

            if (userSaved && createNew && m_input->GetPassword()) {
                authInfo = new Cruxdb::AuthInfo();
                authInfo->setEmail(*(m_input->GetEmail()));
                authInfo->setUnverifiedEmail(*(m_input->GetEmail()));

                auto now = Common::DateTimeUtils::AddMscToNow(DEFAULT_SESSION_TIME_OUT_IN_MSC);
                authInfo->setEmailToken(Cruxdb::AuthUtils::GenerateEmailToken(), now,
                                        Wt::Auth::User::EmailTokenRole::VerifyEmail);

                auto passwdEncoder = Cipher::PassWordEncoder::GetInstance();
                auto salt = passwdEncoder->GenerateSalt();
                auto hash = passwdEncoder->Encode(*(m_input->GetPassword()), salt);
                auto hashMethod = passwdEncoder->HashMethodName();
                authInfo->setPassword(hash, hashMethod, salt);


                authInfo->setStatus(Wt::Auth::User::Status::Normal);

                authInfo->setUser(userSaved);

                auto authInfoAdded = userService->AddAuthInfo(m_requester, authInfo);

                if (authInfoAdded) {
                    //TODO: hard coded identity provider
                    identity = new Cruxdb::AuthIdentity(DEFAULT_LOG_IN_PROVIDER, *m_input->GetEmail());

                    authInfoAdded.modify()->authIdentities().insert(identity);

                    LOG_DEBUG("New user registered successfully");

                    m_output->SetEntity(userSaved);

                    LOG_DEBUG("Mocxygen output: " + m_output->Serialize().serialize());

                } else {
                    throw Common::AppException(AppErrorCode::DB_OPERATION_FAILED,
                                               "Database operation of adding new auth info failed");
                }
            } else {
                throw Common::AppException(AppErrorCode::DB_OPERATION_FAILED,
                                           "Database operation of adding new user failed");
            }
        } catch (Common::AppException &e) {
            //cleanup if not yet
            if (user && createNew) delete user;
            if (authInfo && createNew) delete authInfo;
            if (identity && createNew) delete identity;
            //raise error
            throw e;
        } catch (std::exception &e) {
            //cleanup if not yet
            if (user && createNew) delete user;
            if (authInfo && createNew) delete authInfo;
            if (identity&& createNew) delete identity;
            //raise error
            throw Common::AppException(e);
        }
    }

} /* namespace Mocxygen */
