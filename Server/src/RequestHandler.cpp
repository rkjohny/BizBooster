#include "RequestHandler.h"
#include "ApiExecutor.h"
#include "AppConstant.h"
#include "AppFactory.h"

#include <cpprest/json.h>
#include <cpprest/http_msg.h>
#include <pplx/pplxtasks.h>
#include <AppConstant.h>

#include <iostream>

using namespace Server;

void RequestHandler::HandleGetRequest( web::http::http_request& request )
{

}

void RequestHandler::HandlePutRequest( web::http::http_request& request )
{

}

void RequestHandler::HandlePostRequest( web::http::http_request& request )
{
    web::json::value jresponse;
    
    request
    .extract_json()
    .then( [&]( pplx::task<web::json::value> task )
    {
        try
        {
            web::json::value jrequest = task.get();
           

            if (jrequest.is_object())
            {
                jresponse = ApiExecutor::ExecuteSingleApi(jrequest);
            }
            else if (jrequest.is_array())
            {
                // TODO: handle agregate api
            }
            else
            {
                //TODO: handle bad request
            }
        }
        catch ( std::exception e )
        {
            LOG_ERROR( e.what() );
        }
    } )
    .wait();
    
    std::cout << "Sending Response: " << jresponse.serialize() << std::endl;

    request.reply(web::http::status_codes::OK, jresponse);
}

void RequestHandler::HandleDeleteRequest( web::http::http_request& request )
{

}
