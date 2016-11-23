#ifndef TRADE_X_LISTNER_H
#define TRADE_X_LISTNER_H

#include "RequestHandler.h"
#include "cpprest/http_listener.h"
#include <pplx/pplxtasks.h>


namespace Server
{


class Listener
{
public:
    Listener( utility::string_t serverAddress );
    pplx::task<void> Run();
    pplx::task<void> ShutDown();


private:
    void HandleGet( web::http::http_request& request );
    void HandlePut( web::http::http_request& request );
    void HandlePost( web::http::http_request& request );
    void HandleDelete( web::http::http_request& request );


    web::http::experimental::listener::http_listener m_listener;
    RequestHandler m_requestHandler;
};


} // namespace Server

#endif
