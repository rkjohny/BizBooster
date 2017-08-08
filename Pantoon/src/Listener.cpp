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


#include "Listener.h"

namespace Pantoon {

Listener::Listener(utility::string_t url) : m_listener(web::http::uri(url))
{
    m_listener.support(web::http::methods::GET, std::bind(&Listener::HandleGet, this, std::placeholders::_1));
    m_listener.support(web::http::methods::PUT, std::bind(&Listener::HandlePut, this, std::placeholders::_1));
    m_listener.support(web::http::methods::POST, std::bind(&Listener::HandlePost, this, std::placeholders::_1));
    m_listener.support(web::http::methods::DEL, std::bind(&Listener::HandleDelete, this, std::placeholders::_1));
}

void Listener::HandleGet(web::http::http_request request)
{
    m_requestHandler.HandleGetRequest(request);
}

void Listener::HandlePut(web::http::http_request request)
{
    m_requestHandler.HandlePutRequest(request);
}

void Listener::HandlePost(web::http::http_request request)
{
    m_requestHandler.HandlePostRequest(request);
}

void Listener::HandleDelete(web::http::http_request request)
{
    m_requestHandler.HandleDeleteRequest(request);
}

pplx::task<void> Listener::Run()
{
    return m_listener.open();
}

pplx::task<void> Listener::ShutDown()
{
    return m_listener.close();
}

}