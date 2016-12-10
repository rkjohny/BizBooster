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

#ifndef SERVER_H
#define SERVER_H

#include <memory>
#include <cpprest/uri.h>
#include <cpprest/details/basic_types.h>
#include "Listener.h"



namespace Server {

    class AppServer {
    public:
        AppServer();
        void Run();
        void ShutDown();

    private:
        web::uri_builder uri;
        utility::string_t address;
        std::unique_ptr<Listener> m_listener;
    };


} //namespace Server

#endif
