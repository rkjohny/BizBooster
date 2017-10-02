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

#include "AuthServices.h"
#include "Converter.h"
#include "CipherDef.h"
#include <Wt/Auth/PasswordVerifier.h>
#include <Wt/Auth/PasswordStrengthValidator.h>
#include <Wt/Auth/HashFunction.h>
#include <Wt/Auth/Identity.h>


namespace Cruxdb {

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
        //m_authService.setEmailVerificationRequired(true);
        m_authService.setIdentityPolicy(Wt::Auth::IdentityPolicy::EmailAddress);

        std::unique_ptr<Wt::Auth::PasswordVerifier> verifier = std::make_unique<Wt::Auth::PasswordVerifier>();
        verifier->addHashFunction(std::make_unique<Wt::Auth::BCryptHashFunction>(BECRYPTY_HASH_NUMBER_OF_ITERATION));
        m_passwordService.setVerifier(Common::Converter::DynamicUpCast<Wt::Auth::PasswordVerifier, Wt::Auth::PasswordService::AbstractVerifier>(verifier));
        m_passwordService.setAttemptThrottlingEnabled(true);
        //m_passwordService.setStrengthValidator(std::make_unique<Wt::Auth::PasswordStrengthValidator>());

        //        if (Wt::Auth::GoogleService::configured())
        //            myOAuthServices.push_back(new Wt::Auth::GoogleService(myAuthService));
        //
        //        if (Wt::Auth::FacebookService::configured())
        //            myOAuthServices.push_back(new Wt::Auth::FacebookService(myAuthService));

        m_authServiceConfigured = true;
    }
}

}
