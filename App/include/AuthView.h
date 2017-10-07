// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2011 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef AUTH_WIDGET_H
#define AUTH_WIDGET_H

#include "WtSession.h"
#include <Wt/Auth/AuthWidget.h>
#include "Wt/WIcon.h"
#include "Wt/WImage.h"


namespace BizBooster {

    class AuthView : public Wt::Auth::AuthWidget {
    public:
        AuthView(Wt::Auth::Login &login);

        /* We will use a custom registration view */
        std::unique_ptr<Wt::WWidget> createRegistrationView(const Wt::Auth::Identity &id) override;
        void HandleOAuthEvent(const Wt::Auth::Identity &identity);

    private:
        Wt::Auth::Login &m_login;
        Wt::WIcon* icons;
        std::unique_ptr<Wt::Auth::OAuthProcess> m_wtGoogleOAuthProcesses;
    };

}

#endif // AUTH_WIDGET_H
