#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include "cpprest/http_listener.h"


namespace Server {

    class RequestHandler {
    public:
        void HandleGetRequest(web::http::http_request& request);
        void HandlePutRequest(web::http::http_request& request);
        void HandlePostRequest(web::http::http_request& request);
        void HandleDeleteRequest(web::http::http_request& request);
    };


} //namespace Server
#endif
