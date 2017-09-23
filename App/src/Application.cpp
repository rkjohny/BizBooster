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
#include <Wt/WGlobal.h>
#include <Wt/WServer.h>

#include "AppInitializer.h"
#include "AuthServices.h"
#include "InternalRootRequester.h"
#include "LibCruxdb.h"



namespace BizBooster {

Application::Application(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
    AppInitializer::Initialize();

    root()->addStyleClass("container");
    
    m_theme = std::make_shared<Wt::WBootstrapTheme>();
    setTheme(m_theme);

    useStyleSheet(appRoot() + "resources/css/style.css");
    useStyleSheet(appRoot() + "resources/css/app.css");
    messageResourceBundle().use(appRoot() + "resources/lang/strings");
    messageResourceBundle().use(appRoot() + "resources/template/templates");
    //messageResourceBundle().use(appRoot() + "resources/template/auth_template");

    //    messageResourceBundle().use(appRoot() + "strings");
    //    messageResourceBundle().use(appRoot() + "templates");

    //root()->setContentAlignment(Wt::AlignmentFlag::AlignCenter);

    m_login.changed().connect(this, &Application::HandleAuthEvent);

    std::unique_ptr<LogInWidget> logInWidget = std::make_unique<LogInWidget>(root(), m_login);

    logInWidget->model()->addPasswordAuth(&Cruxdb::AuthServices::GetPasswordService());

    //logInWidget->model()->addOAuth(Session::oAuth());
    logInWidget->setRegistrationEnabled(true);

    logInWidget->processEnvironment();

    root()->addWidget(std::move(logInWidget));
}

void Application::HandleAuthEvent()
{
    if (m_login.loggedIn()) {
        Wt::log("notice") << "User " << m_login.user().id()
                << " logged in.";

        auto dao = Cruxdb::GetUserService();
        auto requester = Common::SingleTon<Cruxdb::InternalRootRequester>::GetInstance();
        auto &&transaction = Wt::Dbo::Transaction(*dao->GetSession());

        auto &authUser = m_login.user();
        auto user = dao->GetUser(requester, authUser);

        Wt::log("notice") << "User.email = " << user->GetEmail();
        //Wt::log("notice") << "(Favourite pet: " << user->favouritePet << ")";

        transaction.commit();
    } else {
        Wt::log("notice") << "User logged out.";
    }
}

} /* end namespace */

std::unique_ptr<Wt::WApplication> createApplication(const Wt::WEnvironment &env)
{
    return std::make_unique<BizBooster::Application>(env);
}

int main(int argc, char **argv)
{
    try {

        BizBooster::AppInitializer::Initialize();

        Wt::WServer server(argc, argv, WTHTTP_CONFIGURATION);

        server.addEntryPoint(Wt::EntryPointType::Application, createApplication);

        server.run();

    } catch (Wt::WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}