#include "Listener.h"

using namespace Server;


Listener::Listener( utility::string_t url )  //: m_listener ( url )
{
    //TODO: add the ahndlers to listener
//     m_listener.support ( web::http::methods::GET, std::bind ( &Listener::HandleGet, this, std::placeholders::_1 ) );
//     m_listener.support ( web::http::methods::PUT, std::bind ( &Listener::HandlePut, this, std::placeholders::_1 ) );
//     m_listener.support ( web::http::methods::POST, std::bind ( &Listener::HandlePost, this, std::placeholders::_1 ) );
//     m_listener.support ( web::http::methods::DEL, std::bind ( &Listener::HandleDelete, this, std::placeholders::_1 ) );
}

void Listener::HandleGet( web::http::http_request& request )
{
    m_requestHandler.HandleGetRequest( request );
}

void Listener::HandlePut( web::http::http_request& request )
{
    m_requestHandler.HandlePutRequest( request );
}

void Listener::HandlePost( web::http::http_request& request )
{
    m_requestHandler.HandlePostRequest( request );
}

void Listener::HandleDelete( web::http::http_request& request )
{
    m_requestHandler.HandleDeleteRequest( request );
}

pplx::task<void> Listener::Run()
{
    return m_listener.open();
    //return pplx::task<void>();
}

pplx::task<void> Listener::ShutDown()
{
    return m_listener.close();
    //return pplx::task<void>();
}