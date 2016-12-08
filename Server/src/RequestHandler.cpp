#include "RequestHandler.h"
#include "ApiExecutor.h"
#include "AppFactory.h"


using namespace Server;

void RequestHandler::HandleGetRequest(web::http::http_request& request)
{

}

void RequestHandler::HandlePutRequest(web::http::http_request& request)
{

}

void RequestHandler::HandlePostRequest(web::http::http_request& request)
{
    web::json::value jresponse;

    request
            .extract_json()
            .then([&](pplx::task<web::json::value> task)
            {
                try {
                    web::json::value jrequest = task.get();

                    LOG_DEBUG("Added new request: " + jrequest.serialize());

                    if (jrequest.is_object()) {
                        jresponse = ApiExecutor::ExecuteSingleApi(jrequest);
                    } else if (jrequest.is_array()) {
                        jresponse = ApiExecutor::ExecuteMultipleApi(jrequest);
                    } else {
                        jresponse = ApiExecutor::BadRequestResponse();
                    }
                } catch (std::exception e) {
                    LOG_ERROR(e.what());
                    jresponse = ApiExecutor::InternalServerErrorResponse();
                }
            })
    .wait();

    LOG_DEBUG("Response: " + jresponse.serialize());

    request.reply(web::http::status_codes::OK, jresponse);
}

void RequestHandler::HandleDeleteRequest(web::http::http_request& request)
{

}
