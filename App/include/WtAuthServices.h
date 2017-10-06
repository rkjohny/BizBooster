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

namespace BizBooster {

    class WtAuthServices {
    private:
        MAKE_STATIC(WtAuthServices);

    public:
        static Wt::Auth::AuthService &GetWtAuthService();

        static Wt::Auth::PasswordService &GetWtPasswordService();

        static void ConfigureAuthService();

        static const Wt::Auth::OAuthService & GetWtGoogleOauthServices();

    private:
        static bool m_authServiceConfigured;
        static Wt::Auth::AuthService m_wtAuthService;
        static Wt::Auth::PasswordService m_wtPasswordService;
        static std::unique_ptr<Wt::Auth::OAuthService> m_wtGoogleOAuthServices;
    };

}

#endif /* AUTHSERVICES_H */

