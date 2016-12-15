//
// Created by rezaul on 12/15/16.
//


#include "AuthService.h"

#include "Dal.h"
#include "Dao.h"

#include "Wt/Auth/Dbo/UserDatabase"

Wt::Auth::AuthService AuthService::myAuthService;
Wt::Auth::PasswordService AuthService::myPasswordService(myAuthService);
MyOAuth AuthService::myOAuthServices;


AuthService::AuthService()
{
}

void AuthService::configureAuth()
{
    myAuthService.setAuthTokensEnabled(true, "logincookie");
    myAuthService.setEmailVerificationEnabled(true);

    Wt::Auth::PasswordVerifier *verifier = new Wt::Auth::PasswordVerifier();
    verifier->addHashFunction(new Wt::Auth::BCryptHashFunction(7));
    myPasswordService.setVerifier(verifier);
    myPasswordService.setAttemptThrottlingEnabled(true);
    myPasswordService.setStrengthValidator
            (new Wt::Auth::PasswordStrengthValidator());

    if (Wt::Auth::GoogleService::configured())
        myOAuthServices.push_back(new Wt::Auth::GoogleService(myAuthService));

    if (Wt::Auth::FacebookService::configured())
        myOAuthServices.push_back(new Wt::Auth::FacebookService(myAuthService));

}

const Wt::Auth::AuthService& AuthService::auth()
{
    return myAuthService;
}

const Wt::Auth::PasswordService& AuthService::passwordAuth()
{
    return myPasswordService;
}

const std::vector<const Wt::Auth::OAuthService *>& AuthService::oAuth()
{
    return myOAuthServices;
}


Wt::Auth::Login& AuthService::login()
{
    return m_login;
}

Wt::Dbo::ptr<Dal::User> AuthService::GetLoggedUser()
{
    if (m_login.loggedIn())
        return GetLoggedUser(m_login.user());
    else
        return Wt::Dbo::ptr<Dal::User>();
}

Wt::Dbo::ptr<Dal::User> AuthService::GetLoggedUser(const Wt::Auth::User& authUser)
{
    return Dal::GetDao()->GetUser(authUser);
}

Wt::Auth::AbstractUserDatabase& AuthService::GetUsers()
{
    return Dal::GetDao()->GetUserDB();
}
