#include "RequestHandler.h"
#include "ApiExecutor.h"
#include "AppConstant.h"
#include "AppFactory.h"

#include <exception>
#include <cpprest/json.h>
#include <pplx/pplxtasks.h>
#include <AppConstant.h>

using namespace Server;

void RequestHandler::HandleGetRequest( web::http::http_request& request )
{

}

void RequestHandler::HandlePutRequest( web::http::http_request& request )
{

}

void RequestHandler::HandlePostRequest( web::http::http_request& request )
{

    request
    .extract_json()
    .then( [&]( pplx::task<web::json::value> task )
    {
        try
        {
            web::json::value jrequest = task.get();
            web::json::value jresponse;

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
}

void RequestHandler::HandleDeleteRequest( web::http::http_request& request )
{

}
