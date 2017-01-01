/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "Dao.h"
#include "Dal.h"
#include "RegisterUserHelper.h"
#include "LogFactory.h"
#include "DateTimeUtils.h"
#include "AuthUtils.h"
#include "PassWordEncoder.h"
#include <Wt/Dbo/WtSqlTraits>


namespace Api {

void RegisterUserHelper::InitAndValidate()
{
    Wt::Dbo::ptr<Dal::User> user = Dal::GetDao()->GetUser(m_requester, m_input->GetEmail());

    if (user) {
        throw Common::AppException(AppErrorCode::USER_ALREADY_EXISTS,
                "User with the email already exists");
    }
}

void RegisterUserHelper::CheckPermission()
{
    if (!(m_requester->HasRole(Role::ROLE_CREATE_SUPER_USER) || 
            m_requester->HasRole(Role::ROLE_SYSTEM_ADMIN))) {
        throw Common::AppException(AppErrorCode::INSIFFICIENT_PRIVILEGE, "Insufficient privilege");
    }
}

void RegisterUserHelper::ExecuteHelper()
{
    LOG_DEBUG("Api input: " + m_input->Serialize().serialize());

    User *user = nullptr;
    Dal::AuthInfo *authInfo = nullptr;
    Dal::AuthInfo::AuthIdentityType *identity = nullptr;
    auto dao = Dal::GetDao();
    
    LOG_DEBUG("Registering new user.");

    try {
        user = new User();
        user->SetName(m_input->GetName());
        user->SetRolesStr(m_input->GetRoles());
        user->SetVersion(m_input->GetVersion());
        user->SetStatusStr(m_input->GetStatus());

        Wt::Dbo::ptr<User> userAdded = dao->RegisterUser(m_requester, user);

        if (userAdded) {
            authInfo = new Dal::AuthInfo();

            authInfo->setEmail(m_input->GetEmail());
            authInfo->setUnverifiedEmail(m_input->GetEmail());

            Wt::WDateTime now;
            Common::DateTimeUtils::AddToCurrentDateTime(now, 2);
            authInfo->setEmailToken(Dal::AuthUtils::GenerateEmailToken(), now, Wt::Auth::User::EmailTokenRole::VerifyEmail);

            auto passwdEncoder = LCrypto::PassWordEncoder::GetInstance();
            auto salt = passwdEncoder->GenerateSalt();
            auto hash = passwdEncoder->Encode(m_input->GetPassword(), salt);
            auto hashMethod = passwdEncoder->HashMethodName();
            authInfo->setPassword(hash, hashMethod, salt);

            authInfo->setStatus(Wt::Auth::User::Status::Normal);

            authInfo->setUser(userAdded);

            Wt::Dbo::ptr<AuthInfo> authInfoAdded = dao->AddAuthInfo(m_requester, authInfo);

            if (authInfoAdded) {
                //TODO: hard coded identity provider
                identity = new Dal::AuthIdentity(DEFAULT_LOG_IN_PROVIDER, m_input->GetEmail());

                authInfoAdded.modify()->authIdentities().insert(identity);

                LOG_DEBUG("New user registered successfully");

                m_output->SetUser(*userAdded);

                LOG_DEBUG("Api output: " + m_output->Serialize().serialize());

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
        if (user) delete user;
        if (authInfo) delete authInfo;
        if (identity) delete identity;
        //raise error
        throw e;
    } catch (std::exception &e) {
        //cleanup if not yet
        if (user) delete user;
        if (authInfo) delete authInfo;
        if (identity) delete identity;
        //raise error
        throw Common::AppException(e);
    }
}

} /* namespace Api */
