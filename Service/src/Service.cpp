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


#include<string>

#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "Service.h"
#include "ServiceDef.h"
#include "LogFactory.h"
#include "ServiceInitializer.h"
#include "ServiceDisposer.h"
#include "CFReaderFactory.h"

using namespace Rest;
using namespace Common;
using namespace std;
using namespace web;
//using namespace http;
using namespace utility;
//using namespace http::experimental::listener;

Service::Service()
{
    //First thing to initialize service
    ServiceInitializer::Initialize();

    auto server_config_reader = Fio::CFReaderFactory::GetConfigReader(SERVICE_CONFIG_FILE_NAME);
    
    utility::string_t protocol = server_config_reader->GetValueOf(SERVICE_HOST_PROTOCOL);
    utility::string_t host_name = server_config_reader->GetValueOf(SERVICE_HOST_NAME);
    utility::string_t port = server_config_reader->GetValueOf(SERVICE_HOST_PORT);
    utility::string_t path = server_config_reader->GetValueOf(SERVICE_APP_PATH);

    utility::string_t addr = U("");
    addr.append(protocol);
    addr.append(U("://"));
    addr.append(host_name);
    addr.append(U(":"));
    addr.append(port);
    
    uri_builder uri(addr);
    uri.append_path(path);

    this->address = uri.to_uri().to_string();
    this->uri = uri;
    
    m_listener = unique_ptr<Listener> (new Listener(this->address));
}

void Service::Run()
{
    m_listener->Run().then([]()
    {
        LOG_DEBUG("Rest service listening ...");
    }).wait();
}

void Service::ShutDown()
{
    m_listener->ShutDown().wait();
}

int main(int argc, char** argv)
{
    UNUSED(argc), UNUSED(argv);
    
    Service server;

    LOG_DEBUG("Rest service starting ...");

    server.Run();

    LOG_DEBUG("Rest service started.");
    while (1) {
        std::string input;
        LOG_DEBUG("Please enter EXIT to exit.");

        std::cin >> input;
        if (input.compare("EXIT") == 0) {
            break;
        }
#ifdef _WIN32
        Sleep(1000);
#else
        sleep(1);
#endif
    }

    LOG_DEBUG("Rest service is shutting down ...");

    server.ShutDown();
    ServiceDisposer::Dispose();

#ifdef _WIN32
    Sleep(1000);
#else
    sleep(1);
#endif

    std::cout << "Rest service stopped.";
    
    return 0;
}
