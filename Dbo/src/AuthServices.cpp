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

#include "AuthServices.h"

#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/PasswordStrengthValidator>
#include <Wt/Auth/HashFunction>


namespace Dal {

bool AuthServices::m_authServiceConfigured = false;
Wt::Auth::AuthService AuthServices::m_authService;
Wt::Auth::PasswordService AuthServices::m_passwordService(AuthServices::m_authService);

Wt::Auth::AuthService& AuthServices::GetAuthService()
{
    return m_authService;
}

Wt::Auth::PasswordService& AuthServices::GetPasswordService()
{
    return m_passwordService;
}

void AuthServices::ConfigureAuthService()
{
    if (!m_authServiceConfigured) {
        m_authService.setAuthTokensEnabled(true, "logincookie");
        m_authService.setEmailVerificationEnabled(true);
        m_authService.setEmailVerificationRequired(true);
        //m_authService.setIdentityPolicy(Wt::Auth::IdentityPolicy::EmailAddressIdentity);

        Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
        verifier->addHashFunction(new Wt::Auth::BCryptHashFunction(7));
        m_passwordService.setVerifier(verifier);
        m_passwordService.setAttemptThrottlingEnabled(true);
        m_passwordService.setStrengthValidator(new Wt::Auth::PasswordStrengthValidator());

        //        if (Wt::Auth::GoogleService::configured())
        //            myOAuthServices.push_back(new Wt::Auth::GoogleService(myAuthService));
        //
        //        if (Wt::Auth::FacebookService::configured())
        //            myOAuthServices.push_back(new Wt::Auth::FacebookService(myAuthService));

        m_authServiceConfigured = true;
    }
}

}
