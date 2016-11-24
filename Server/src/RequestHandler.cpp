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

            if (!jrequest.is_null() && jrequest.is_object())
            {
                if (!jrequest.is_array())
                {
                    const web::json::value &jvalApi = jrequest.at(JSON_API);
                    const web::json::value &jvalData = jrequest.at(JSON_DATA);

                    if (!jvalApi.is_null() && !jvalData.is_null() &&
                        jvalApi.is_string() && jvalData.is_object())
                    {
                        jresponse = ApiExecutor::ExecuteSingleApi(jrequest);
                    }
                    else
                    {
                        //TODO: handle bad request
                    }
                }
                else
                {
                    // TODO: handle agregate api
                }
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

        //input.as_array();
    } ).wait();
}

void RequestHandler::HandleDeleteRequest( web::http::http_request& request )
{

}
