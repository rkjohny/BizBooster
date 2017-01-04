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


#include <Wt/WServer>
#include <Wt/WBootstrapTheme>


#include "AppInitializer.h"

namespace WebApp {

Application::Application(const Wt::WEnvironment &env) : Wt::WApplication(env)
{
    //root()->addWidget(new Wt::WText("Hello World")); // show some text

    root()->addStyleClass("container");
    setTheme(new Wt::WBootstrapTheme());

    useStyleSheet("css/style.css");

    m_loginWidge = new WebApp::LoginWidget(root());
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