#ifndef TRADE_X_SERVER_H
#define TRADE_X_SERVER_H

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
