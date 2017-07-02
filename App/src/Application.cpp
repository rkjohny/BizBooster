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
#include "LogInWidget.h"

#include <Wt/WServer>
#include <Wt/WBootstrapTheme>

#include "AppInitializer.h"
#include "AuthServices.h"
#include "InternalRootRequester.h"
#include "LibCruxdb.h"



namespace BizBooster {

Application::Application(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
    AppInitializer::Initialize();

    root()->addStyleClass("container");
    setTheme(new Wt::WBootstrapTheme());

    useStyleSheet(appRoot() + "resources/css/style.css");
    useStyleSheet(appRoot() + "resources/css/app.css");
    messageResourceBundle().use(appRoot() + "resources/lang/strings");
    messageResourceBundle().use(appRoot() + "resources/template/templates");
    //messageResourceBundle().use(appRoot() + "resources/template/auth_template");

    //    messageResourceBundle().use(appRoot() + "strings");
    //    messageResourceBundle().use(appRoot() + "templates");

    //root()->setContentAlignment(Wt::AlignmentFlag::AlignCenter);

    m_login.changed().connect(this, &Application::HandleAuthEvent);

    LogInWidget *logInWidget = new LogInWidget(root(), m_login);

    logInWidget->model()->addPasswordAuth(&Cruxdb::AuthServices::GetPasswordService());

    //logInWidget->model()->addOAuth(Session::oAuth());
    logInWidget->setRegistrationEnabled(true);

    logInWidget->processEnvironment();

    root()->addWidget(logInWidget);
}

void Application::HandleAuthEvent()
{
    if (m_login.loggedIn()) {
        Wt::log("notice") << "User " << m_login.user().id()
                << " logged in.";

        auto dao = Cruxdb::GetDao();
        auto requester = Cruxdb::InternalRootRequester::GetInstance();
        auto transaction = dao->BeginTransaction(requester);

        auto &authUser = m_login.user();
        auto user = dao->GetUser(requester, authUser);

        Wt::log("notice") << "User.email = " << user->GetEmail();
        //Wt::log("notice") << "(Favourite pet: " << user->favouritePet << ")";

        dao->CommitTransaction(requester, transaction);

    } else {
        Wt::log("notice") << "User logged out.";
    }
}

} /* end namespace */

Wt::WApplication* createApplication(const Wt::WEnvironment &env)
{
    return new BizBooster::Application(env);
}

int main(int argc, char **argv)
{
    try {

        BizBooster::AppInitializer::Initialize();

        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(Wt::Application, createApplication);

        server.run();

    } catch (Wt::WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}