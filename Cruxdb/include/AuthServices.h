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

#ifndef AUTHSERVICES_H
#define AUTHSERVICES_H

#include "AppCommonDef.h"

#include <Wt/Auth/AuthService.h>
#include <Wt/Auth/PasswordService.h>

namespace Cruxdb {

class AuthServices {
private:
    MAKE_STATIC(AuthServices);

public:
    static Wt::Auth::AuthService &GetAuthService();

    static Wt::Auth::PasswordService &GetPasswordService();

    static void ConfigureAuthService();

private:
    static bool m_authServiceConfigured;
    static Wt::Auth::AuthService m_authService;
    static Wt::Auth::PasswordService m_passwordService;
};

}

#endif /* AUTHSERVICES_H */

