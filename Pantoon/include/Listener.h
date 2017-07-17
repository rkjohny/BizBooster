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

#ifndef LISTNER_H
#define LISTNER_H

#include "RequestHandler.h"
#include "cpprest/http_listener.h"
#include <pplx/pplxtasks.h>


namespace Pantoon {

    class Listener {
    public:
        Listener(utility::string_t serverAddress);
        pplx::task<void> Run();
        pplx::task<void> ShutDown();


    private:
        void HandleGet(web::http::http_request request);
        void HandlePut(web::http::http_request request);
        void HandlePost(web::http::http_request request);
        void HandleDelete(web::http::http_request request);


        web::http::experimental::listener::http_listener m_listener;
        RequestHandler m_requestHandler;
    };


} // namespace Server

#endif
