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

#ifndef W_APPLICATION_H
#define W_APPLICATION_H

#include <Wt/WApplication.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WBootstrapTheme.h>

#include "DboTypes.h"
#include "AuthView.h"

namespace BizBooster {

    class Application : public Wt::WApplication {
    public:
        Application(const Wt::WEnvironment &env);

        ~Application();

        void HandleAuthEvent();

        void HandleInternalPath(const std::string &internalPath);

        void HandleOAuthEvent(const Wt::Auth::Identity &identity);

    private:
        AuthView *m_logInWidget;
        Wt::Auth::Login m_login;
        std::shared_ptr<Wt::WBootstrapTheme> m_theme;

    };

}

#endif /* W_APPLICATION_H */