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
#include "PasswordEncoder.h"
#include "LibCipher.h"
#include <Wt/Dbo/WtSqlTraits.h>
#include <BlockExecutor.h>


namespace Mocxygen {


    void SaveUserHelper::ExecuteHelper() noexcept(false) {
        LOG_DEBUG("Mocxygen input: " + m_input->Serialize().serialize());
        bool createNew = false;


        if (!(m_requester->HasRole(Cruxdb::Role::ROLE_CREATE_SUPER_USER) ||
              m_requester->HasRole(Cruxdb::Role::ROLE_SYSTEM_ADMIN))) {
            throw Common::AppException(AppErrorCode::INSIFFICIENT_PRIVILEGE, "Insufficient privilege");
        }

        Wt::Dbo::ptr<Cruxdb::User> user = nullptr;
        Wt::Dbo::ptr<Cruxdb::AuthInfo> authInfo = nullptr;
        Wt::Dbo::ptr<Cruxdb::AuthIdentityType> identity = nullptr;
        auto userService = Cruxdb::GetUserService();
        
        if (!m_input->GetId()) {
            createNew = true;
        }


        if (m_input->GetEmail()) {
            m_user = userService->GetUser(m_requester, *m_input->GetEmail());
            if (createNew) {
                if (m_user) {
                    throw Common::AppException(AppErrorCode::USER_ALREADY_EXISTS, "User with the email already exists");
                }
            } else {
                if (!m_user) {
                    throw Common::AppException(AppErrorCode::USER_NOT_FOUND, "User with the email not found");
                }
            }
        } else {
            throw Common::AppException(AppErrorCode::INVALID_ARGUMENT, "User email is empty");
        }
        

        LOG_DEBUG("Registering new user.");

        try {
            BlockExecutor blockExecutor;
            if (createNew) {
                user = Wt::Dbo::make_ptr<Cruxdb::User>();
            } else {
                user = m_user;
            }


            blockExecutor.Execute(m_input->GetName() != boost::none, [&]() -> void {
                user.modify()->SetLogin(*(m_input->GetName()));
            });


            blockExecutor.Execute(m_input->GetRoles() != boost::none, [&]() -> void {
                user.modify()->SetRolesStr(*(m_input->GetRoles()));
            });


            blockExecutor.Execute(m_input->GetStatus() != boost::none, [&]() -> void {
                user.modify()->SetStatusStr(*(m_input->GetStatus()));
            });

            //user->SetVersion(m_input->GetVersion());

            Wt::Dbo::ptr<Cruxdb::User> userSaved;

            if (blockExecutor.IsInvoked()) {
                userSaved = userService->SaveEntity(m_requester, user);
            }

            if (userSaved && createNew && m_input->GetPassword()) {
                authInfo = Wt::Dbo::make_ptr<Cruxdb::AuthInfo>();
                authInfo.modify()->setEmail(*(m_input->GetEmail()));
                authInfo.modify()->setUnverifiedEmail(*(m_input->GetEmail()));

                Wt::WDateTime expiresAfter = Common::DateTimeUtils::AddDaysToNow(DEFAULT_TOKEN_TIME_OUT_IN_DAYS);
                authInfo.modify()->setEmailToken(Cruxdb::AuthUtils::GenerateEmailToken(), expiresAfter,
                                        Wt::Auth::EmailTokenRole::VerifyEmail);

                auto passwdEncoder = Cipher::GetPasswordEncoder();
                auto salt = passwdEncoder->GenerateSalt();
                auto hash = passwdEncoder->Encode(*(m_input->GetPassword()), salt);
                auto hashMethod = passwdEncoder->HashMethodName();
                authInfo.modify()->setPassword(hash, hashMethod, salt);


                authInfo.modify()->setStatus(Wt::Auth::User::Status::Normal);

                authInfo.modify()->setUser(userSaved);

                auto authInfoAdded = userService->AddAuthInfo(m_requester, authInfo);

                if (authInfoAdded) {
                    //TODO: hard coded identity provider
                    identity = Wt::Dbo::make_ptr<Cruxdb::AuthIdentityType>(DEFAULT_LOG_IN_PROVIDER, *m_input->GetEmail());

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
            //raise error
            throw e;
        } catch (std::exception &e) {
            //raise error
            throw Common::AppException(e);
        }
    }

} /* namespace Mocxygen */
