/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


#include "AppContainer.h"
#include <Wt/Auth/PasswordVerifier>
#include <Wt/Auth/HashFunction>
#include <Wt/Auth/PasswordStrengthValidator>

namespace WebApp {

bool AppContainer::m_authServiceConfigured = false;
Wt::Auth::AuthService AppContainer::m_authService;
Wt::Auth::PasswordService AppContainer::m_passwordService(AppContainer::m_authService);

Wt::Auth::AuthService& AppContainer::GetAuthService()
{
    return m_authService;
}

Wt::Auth::PasswordService& AppContainer::GetPasswordService()
{
    return m_passwordService;
}

void AppContainer::ConfigureAuthService()
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