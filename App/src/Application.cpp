/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
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

namespace WebApp {

Application::Application(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
    AppInitializer::Initialize();
    
    root()->addStyleClass("container");
    setTheme(new Wt::WBootstrapTheme());

    useStyleSheet(appRoot() + "resource/css/style.css");
    useStyleSheet(appRoot() + "resource/css/app.css");
    messageResourceBundle().use(appRoot() + "resource/lang/strings");
    messageResourceBundle().use(appRoot() + "resource/template/templates");

//    messageResourceBundle().use(appRoot() + "strings");
//    messageResourceBundle().use(appRoot() + "templates");
        
    //root()->setContentAlignment(Wt::AlignmentFlag::AlignCenter);
    
//    Dal::AuthServices::ConfigureAuthService();
    
    LogInWidget *logInWidget = new LogInWidget(m_login);

    logInWidget->model()->addPasswordAuth(&Dal::AuthServices::GetPasswordService());
    
    //logInWidget->model()->addOAuth(Session::oAuth());
    logInWidget->setRegistrationEnabled(true);

    logInWidget->processEnvironment();

    root()->addWidget(logInWidget);
}

} /* end namespace */

Wt::WApplication* createApplication(const Wt::WEnvironment &env)
{
    return new WebApp::Application(env);
}

int main(int argc, char **argv)
{
    try {

        WebApp::AppInitializer::Initialize();

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