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


#include <Wt/WText>
#include <Wt/WBreak>
#include <Wt/WPushButton>

#include "LoginWidget.h"

#include <iostream>
#include <cpprest/details/basic_types.h>
#include <cpprest/http_client.h>

namespace WebApp {

LoginWidget::LoginWidget(Wt::WContainerWidget *parent)
{
    m_userName = new Wt::WLineEdit(parent);
    m_userName->setAutoComplete(true);
    m_userName->setPlaceholderText("User name");
    new Wt::WBreak(parent);

    m_password = new Wt::WLineEdit(parent);
    m_password->setEchoMode(Wt::WLineEdit::EchoMode::Password);
    m_password->setPlaceholderText("Password");
    new Wt::WBreak(parent);

    m_login = new Wt::WPushButton(parent);
    m_login->setText("Login");
    m_login->clicked().connect(this, &LoginWidget::Login);

}

LoginWidget::~LoginWidget()
{
    

}

void LoginWidget::Login()
{
    utility::string_t port = U("8088");
    utility::string_t address = U("http://localhost:");
    address.append(port);

    web::http::uri uri = web::http::uri(address);

    web::http::client::http_client restClient(web::http::uri_builder(uri).append_path(U("/bizbooster/rest")).to_uri());
    web::json::value jvalRequest;
    jvalRequest[U("@api")] = web::json::value::string(U("login"));
    web::json::value data;
    data[U("user_name")] = web::json::value::string(U(m_userName->valueText().toUTF8().c_str()));
    data[U("password")] = web::json::value::string(U(m_password->valueText().toUTF8().c_str()));
    jvalRequest[U("@data")] = data;

    //utility::string_t requestData = jvalRequest.serialize();

    web::http::http_request request(web::http::methods::POST);
    request.headers().add(U("Content-Type"), U("application/json"));
    request.set_body(jvalRequest);
    
    std::cout << "************************** MAKING REQUEST ***************" << std::endl;
    
    web::http::http_response response = restClient.request(request).get();
    
    std::cout << "************************** RESPONSE *******" << std::endl;
    std::cout << response.to_string() << std::endl;
    
    std::cout << "************************** RESPONSE DATA *******" << std::endl;
    
    web::json::value jvalResponse = response.extract_json().get();
    
    std::cout <<  jvalResponse.serialize() << std::endl;
    
//    response.extract_json([](web::json::value data) {
//        std::cout << data.serialize() << std::endl;
//    }).wait();

    std::cout << "************************** END RESPONSE ********************" << std::endl;
}

}
