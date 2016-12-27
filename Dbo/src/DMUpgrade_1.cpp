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
#include "LibCryptoDef.h"

namespace Dal {

void DMUpgrade_1::Execute()
{    
    //Creating super user;
    User *user = new User();
    user->SetName("admin");
    user->SetEmail("admin@bizbooster.com");
    //user->SetPassword("admin");
    user->SetRoles(Role::ROLE_CREATE_SUPER_USER);
    user->SetStatus(Status::V);
    //user->AddIdentity("loginname", "admin");
    
    User loggedUser = User();
    Wt::Dbo::ptr<User> userAdded = Dal::GetDao()->RegisterUser(loggedUser, user);
    
    if (userAdded) {
        AuthInfo *authInfo = new AuthInfo();
        
        authInfo->setEmail(user->GetEmail());

        Wt::WDateTime now;
        Common::DateTimeUtils::AddToCurrentDateTime(now, 2);
        authInfo->setEmailToken(Dal::AuthUtils::GenerateEmailToken(), now, Wt::Auth::User::EmailTokenRole::VerifyEmail);
        
        auto passwdEncoder = LCrypto::PassWordEncoder::GetInstance();
        auto salt = passwdEncoder->GenerateSalt();
        auto hash = passwdEncoder->Encode("admin", salt);
        auto hashMethod = passwdEncoder->HashMethodName();
        authInfo->setPassword(hash, hashMethod, salt);

        authInfo->setStatus(Wt::Auth::User::Status::Normal);

        authInfo->setUnverifiedEmail(user->GetEmail());
        authInfo->setUser(userAdded);

        Wt::Dbo::ptr<AuthInfo> authInfoAdded = Dal::GetDao()->AddAuthInfo(loggedUser, authInfo);

    }
}

}