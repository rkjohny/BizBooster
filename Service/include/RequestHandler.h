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

#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "cpprest/http_listener.h"


namespace Rest {

    class RequestHandler {
    public:
        void HandleGetRequest(web::http::http_request& request);
        void HandlePutRequest(web::http::http_request& request);
        void HandlePostRequest(web::http::http_request& request);
        void HandleDeleteRequest(web::http::http_request& request);
    };


} //namespace Server
#endif
