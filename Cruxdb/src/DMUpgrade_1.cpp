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

#include "DMUpgrade_1.h"
#include <memory>
#include <string>
#include <PasswordEncoder.h>
#include "DateTimeUtils.h"
#include "AuthUtils.h"
#include "LibCruxdb.h"
#include "Roles.h"
#include "LibCipher.h"
#include "CipherDef.h"
#include "AppException.h"
#include "Requester.h"
#include "InternalRootRequester.h"
#include "CruxdbDef.h"


namespace Cruxdb {

void DMUpgrade_1::Execute() noexcept(false)
{
    //TODO: hard coded super user info 
    std::string superUserName = "admin";
    std::string superUserEmail = "admin@bizbooster.com";
    std::string superUserPassword = "admin";
    std::string superUserIdentityProvider = DEFAULT_LOG_IN_PROVIDER;
    std::string superUserIdentity = "admin@bizbooster.com";

    Wt::Dbo::ptr<User> user = nullptr;
    Wt::Dbo::ptr<Cruxdb::AuthInfo> authInfo = nullptr;
    Wt::Dbo::ptr<Cruxdb::AuthIdentityType> identity = nullptr;

    auto dao = Cruxdb::GetUserService();
    
    try {
        //Creating super user;
        user = Wt::Dbo::make_ptr<User>();
        user.modify()->SetName(superUserName);
        user.modify()->SetRoles(Role::ROLE_CREATE_SUPER_USER);
        user.modify()->SetStatus(Status::V);

        std::shared_ptr<Requester> requester = std::make_shared<InternalRootRequester>();
        Wt::Dbo::ptr<User> userAdded = dao->SaveEntity(requester, user);

        if (userAdded) {
            authInfo = Wt::Dbo::make_ptr<Cruxdb::AuthInfo>();

            authInfo.modify()->setEmail(superUserEmail);
            authInfo.modify()->setUnverifiedEmail(superUserEmail);

            auto now = Common::DateTimeUtils::AddMsecToNow(DEFAULT_SESSION_TIME_OUT_IN_SEC);
            authInfo.modify()->setEmailToken(Cruxdb::AuthUtils::GenerateEmailToken(), now, Wt::Auth::EmailTokenRole::VerifyEmail);

            auto passwdEncoder = Cipher::GetPasswordEncoder();
            auto salt = passwdEncoder->GenerateSalt();
            auto hash = passwdEncoder->Encode(superUserPassword, salt);
            auto hashMethod = passwdEncoder->HashMethodName();
            authInfo.modify()->setPassword(hash, hashMethod, salt);

            authInfo.modify()->setStatus(Wt::Auth::User::Status::Normal);

            authInfo.modify()->setUser(userAdded);

            Wt::Dbo::ptr<Cruxdb::AuthInfo> authInfoAdded = dao->AddAuthInfo(requester, authInfo);

            if (authInfoAdded) {
                //identity = new Cruxdb::AuthInfo::AuthIdentityType(superUserIdentityProvider, superUserIdentity);

                identity = Wt::Dbo::make_ptr<Cruxdb::AuthIdentityType>(superUserIdentityProvider, superUserIdentity);
                authInfoAdded.modify()->authIdentities().insert(identity);

                // Wt::Cruxdb::ptr<AuthInfo::AuthIdentityType> identityAdded =
                // Cruxdb::GetUserService()->AddIdentity(identity);
            } else {
                throw Common::AppException(AppErrorCode::DB_OPERATION_FAILED,
                        "Database operation of adding auth info of super user failed");
            }
        } else {
            throw Common::AppException(AppErrorCode::DB_OPERATION_FAILED,
                    "Database operation of adding super user failed");
        }
    } catch (Common::AppException &e) {
        //raise error
        throw e;
    } catch (std::exception &e) {
        //raise error
        throw Common::AppException(e);
    }
}

}