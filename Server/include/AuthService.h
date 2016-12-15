//
// Created by rezaul on 12/15/16.
//

#ifndef AUTH_SERVICE_H
#define AUTH_SERVICE_H


#include "Wt/Auth/AuthService"
#include "Wt/Auth/HashFunction"
#include "Wt/Auth/PasswordService"
#include "Wt/Auth/PasswordStrengthValidator"
#include "Wt/Auth/PasswordVerifier"
#include "Wt/Auth/GoogleService"
#include "Wt/Auth/FacebookService"
#include "Wt/Auth/Dbo/AuthInfo"
#include "Wt/Auth/Dbo/UserDatabase"

#include "Wt/Auth/Login"
#include <Wt/WGlobal>

#include "User.h"



class MyOAuth : public std::vector<const Wt::Auth::OAuthService *> {
public:
    ~MyOAuth()
    {
        for (unsigned i = 0; i < size(); ++i)
            delete (*this)[i];
    }
};


class AuthService {
public:
    AuthService();

    static const Wt::Auth::AuthService& auth();

    static const Wt::Auth::PasswordService& passwordAuth();

    static const std::vector<const Wt::Auth::OAuthService *>& oAuth();

    static void configureAuth();

    Wt::Auth::Login& login();

    Wt::Dbo::ptr<Dal::User> GetLoggedUser();

    Wt::Dbo::ptr<Dal::User> GetLoggedUser(const Wt::Auth::User& authUser);

    Wt::Auth::AbstractUserDatabase& GetUsers();

private:

    Wt::Auth::Login m_login;



    static Wt::Auth::AuthService myAuthService;
    static Wt::Auth::PasswordService myPasswordService;
    static MyOAuth myOAuthServices;
};


#endif //BIZBOOSTER_AUTHSERVICE_H
