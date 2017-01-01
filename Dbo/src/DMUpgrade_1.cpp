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

#include "DMUpgrade_1.h"
#include <memory>
#include <string>
#include <PassWordEncoder.h>
#include "DateTimeUtils.h"
#include "AuthUtils.h"
#include "Dal.h"
#include "Roles.h"
#include "LCrypto.h"
#include "CryptoDef.h"
#include "AppException.h"
#include "Requester.h"
#include "InternalRootRequester.h"
#include "DboDef.h"

namespace Dal {

void DMUpgrade_1::Execute()
{
    //TODO: hard coded super user info 
    std::string superUserName = "admin";
    std::string superUserEmail = "admin@nilavo.com";
    std::string superUserPassword = "admin";
    std::string superUserIdentityProvider = DEFAULT_LOG_IN_PROVIDER;
    std::string superUserIdentity = "admin";

    User *user = nullptr;
    Dal::AuthInfo *authInfo = nullptr;
    Dal::AuthInfo::AuthIdentityType *identity = nullptr;

    auto dao = Dal::GetDao();
    
    try {
        //Creating super user;
        user = new User();
        user->SetName(superUserName);
        user->SetRoles(Role::ROLE_CREATE_SUPER_USER);
        user->SetStatus(Status::V);

        Requester *requester = InternalRootRequester::GetInstance();
        Wt::Dbo::ptr<User> userAdded = dao->RegisterUser(requester, user);

        if (userAdded) {
            authInfo = new Dal::AuthInfo();

            authInfo->setEmail(superUserEmail);
            authInfo->setUnverifiedEmail(superUserEmail);

            Wt::WDateTime now;
            Common::DateTimeUtils::AddToCurrentDateTime(now, 2);
            authInfo->setEmailToken(Dal::AuthUtils::GenerateEmailToken(), now, Wt::Auth::User::EmailTokenRole::VerifyEmail);

            auto passwdEncoder = LCrypto::PassWordEncoder::GetInstance();
            auto salt = passwdEncoder->GenerateSalt();
            auto hash = passwdEncoder->Encode(superUserPassword, salt);
            auto hashMethod = passwdEncoder->HashMethodName();
            authInfo->setPassword(hash, hashMethod, salt);

            authInfo->setStatus(Wt::Auth::User::Status::Normal);

            authInfo->setUser(userAdded);

            Wt::Dbo::ptr<AuthInfo> authInfoAdded = dao->AddAuthInfo(requester, authInfo);

            if (authInfoAdded) {
                identity = new Dal::AuthIdentity(superUserIdentityProvider, superUserIdentity);

                authInfoAdded.modify()->authIdentities().insert(identity);

                // Wt::Dbo::ptr<AuthInfo::AuthIdentityType> identityAdded =
                // Dal::GetDao()->AddIdentity(identity);                                  
            } else {
                throw Common::AppException(AppErrorCode::DB_OPERATION_FAILED,
                        "Database operation of adding auth info of super user failed");
            }
        } else {
            throw Common::AppException(AppErrorCode::DB_OPERATION_FAILED,
                    "Database operation of adding super user failed");
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

}