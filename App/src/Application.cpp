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

#include "Application.h"
#include <Wt/WServer.h>

#include "AppInitializer.h"
#include "WtAuthServices.h"
#include "InternalRootRequester.h"
#include "LibCruxdb.h"
#include "WtUserService.h"
#include "AppDisposer.h"


namespace BizBooster {

    Application::Application(const Wt::WEnvironment &env) : Wt::WApplication(env) {
        AppInitializer::Initialize();

        root()->addStyleClass("container");

        m_theme = std::make_shared<Wt::WBootstrapTheme>();
        setTheme(m_theme);

        useStyleSheet(appRoot() + "resources/style.css");
        useStyleSheet(appRoot() + "contents/css/app.css");

        messageResourceBundle().use(appRoot() + "contents/templates/bootstrap_theme");
        messageResourceBundle().use(appRoot() + "contents/templates/bootstrap3_theme");
        messageResourceBundle().use(appRoot() + "contents/templates/wt");
        messageResourceBundle().use(appRoot() + "contents/templates/auth_strings");

        //root()->setContentAlignment(Wt::AlignmentFlag::AlignCenter);

        m_login.changed().connect(this, &Application::HandleAuthEvent);

        WtAuthServices::GetWtGoogleOauthProcess()->authenticated().connect(this, &Application::HandleOAuthEvent);

        m_logInWidget = root()->addWidget(std::make_unique<AuthView>(m_login));

        Wt::WApplication::instance()->internalPathChanged().connect(this, &Application::HandleInternalPath);
    }

    Application::~Application() {
        AppDisposer::Dispose();
    }

    void Application::HandleAuthEvent() {
        if (m_login.loggedIn()) {
            Wt::log("notice") << "User " << m_login.user().id()
                              << " logged in.";

            auto userService = Common::SingleTon<WtUserService>::GetInstance();
            std::shared_ptr<Cruxdb::InternalRootRequester> requester = std::make_shared<Cruxdb::InternalRootRequester>();

            auto &&transaction = Wt::Dbo::Transaction(*userService->GetSession());

            const Wt::Auth::User &authUser = m_login.user();
            Wt::Dbo::ptr<Cruxdb::User> user = userService->GetUser(requester, authUser);

            Wt::log("notice") << "User.email = " << user->GetEmail();

            transaction.commit();

            Wt::WApplication::instance()->setInternalPath("/home");
            HandleInternalPath(Wt::WApplication::instance()->internalPath());
        } else {
            Wt::log("notice") << "User logged out.";
            HandleInternalPath("/login");
        }
    }

    void Application::HandleInternalPath(const std::string &internalPath) {
        if (m_login.loggedIn()) {
            if (internalPath == "/google-oauth-finish") {

            } else if (internalPath == "/profile") {

            } else {
                Wt::WApplication::instance()->setInternalPath("/home", true);
            }
        } else {
            Wt::WApplication::instance()->setInternalPath("/login", true);
        }
    }

    void Application::HandleOAuthEvent(const Wt::Auth::Identity &identity) {
        std::cout << "Authenticated using Google OAuth service !!" << std::endl;
    }

} /* end namespace */

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment &env) {
    return std::make_unique<BizBooster::Application>(env);
}

int main(int argc, char **argv) {
    try {

        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

        //BizBooster::AppInitializer::Initialize();

        server.run();

    } catch (Wt::WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}