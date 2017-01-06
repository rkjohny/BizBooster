/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AppContainer.h
 * Author: Rezaul Karim
 *
 * Created on January 6, 2017, 12:01 PM
 */

#ifndef APP_CONTAINER_H
#define APP_CONTAINER_H

#include <Wt/Auth/AuthService>
#include <Wt/Auth/PasswordService>

#include "AppDef.h"

namespace WebApp {

class AppContainer {
public:

    static Wt::Auth::AuthService &GetAuthService();
    static Wt::Auth::PasswordService &GetPasswordService();
    
    static void ConfigureAuthService();
    
private:
    MAKE_STATIC(AppContainer);

    static bool m_authServiceConfigured;
    static Wt::Auth::AuthService m_authService;
    static Wt::Auth::PasswordService m_passwordService;
};

}


#endif /* APPCONTAINER_H */

