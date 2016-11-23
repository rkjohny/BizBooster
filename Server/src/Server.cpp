#include<string>

#if defined (_WIN32) || defined (WIN32)
#include <windows.h>
#else
#include <unistd.h>
#endif

#include "Server.h"
#include "AppConstant.h"
#include "AppFactory.h"
#include "ServerInitializer.h"
#include "ServerDisposer.h"


using namespace Server;
using namespace Common;
using namespace std;
using namespace web;
//using namespace http;
using namespace utility;
//using namespace http::experimental::listener;

AppServer::AppServer()
{
    utility::string_t address = U( SERVER_ADDRESS );
    address.append( U( ":" ) );
    address.append( U( SERVER_PORT ) );

    uri_builder uri( address );
    //uri.append_path(U("http://localhost:8088/tradex"));
    auto addr = uri.to_uri().to_string();
    this->address = U( "http://localhost:8088/tradex" );
    this->uri = uri;
    m_listener = unique_ptr<Listener> ( new Listener( this->address ) );
}

void AppServer::Run()
{
    m_listener->Run().then( []()
    {
        //Logger::getLogger(SERVER).debug("Server listening....");
        LOG_DEBUG( "listening............" );
    } ).wait();
}

void AppServer::ShutDown()
{
    m_listener->ShutDown().wait();
}


int main( int argc, char** argv )
{
    AppServer server;
    ServerInitializer::Initialize();
    LOG_DEBUG( "Starting TradeXServer..." );

    server.Run();

    LOG_DEBUG( "TradeXServer started." );
    while ( 1 )
    {
        std::string input;
        LOG_DEBUG( "Please enter EXIT to exit." );

        std::cin >> input;
        if ( input.compare( "EXIT" ) == 0 )
        {
            break;
        }
#ifdef _WIN32
        Sleep( 100 );
#else
        sleep( 100 );
#endif
    }

    LOG_DEBUG( "TradeXServer is shutting down ..." );
    LOG_DEBUG( "TradeXServer is shutting down ..." );

    server.ShutDown();
    ServerDisposer::Dispose();

#ifdef _WIN32
    Sleep( 1000 );
#else
    sleep( 1000 );
#endif

    return 0;
}
