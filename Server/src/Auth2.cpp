/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WServer>

#include <Wt/Auth/AuthModel>
#include <Wt/Auth/AuthWidget>
#include <Wt/Auth/PasswordService>

#include <Wt/WBootstrapTheme>

#include "AuthWidget.h"

#include "AuthService.h"

#include "Dal.h"
#include "Dao.h"

class AuthApplication : public Wt::WApplication {
public:
    AuthApplication(const Wt::WEnvironment &env)
            : Wt::WApplication(env)
    {
        m_auth_service.login().changed().connect(this, &AuthApplication::authEvent);

                
        setTheme(new Wt::WBootstrapTheme());
        root()->addStyleClass("container");
        
        useStyleSheet("css/style.css");
        
        messageResourceBundle().use("strings");
        messageResourceBundle().use("templates");

        AuthWidget *authWidget = new AuthWidget(m_auth_service);

        authWidget->model()->addPasswordAuth(&AuthService::passwordAuth());
        authWidget->model()->addOAuth(AuthService::oAuth());
        authWidget->setRegistrationEnabled(true);

        authWidget->processEnvironment();

        root()->addWidget(authWidget);

    }

    void authEvent()
    {
        if (m_auth_service.login().loggedIn()) {

            const Wt::Auth::User &u = m_auth_service.login().user();

            Wt::log("notice") << "User " << u.id()
                              << " logged in.";

            auto user = m_auth_service.GetLoggedUser(u);
            Wt::log("notice") << "UserId= " << user->GetId() << " User email= " << user->GetEmail();

            //Wt::log("notice") << "(Favourite pet: " << user->favouritePet << ")";
        } else
            Wt::log("notice") << "User logged out.";
    }

private:
    AuthService m_auth_service;
};

Wt::WApplication *createApplication(const Wt::WEnvironment &env)
{
    return new AuthApplication(env);
}

int main(int argc, char **argv)
{
    try {
        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(Wt::Application, createApplication);

        AuthService::configureAuth();

        Dal::LoadLibrary();

        server.run();

    } catch (Wt::WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }
}
