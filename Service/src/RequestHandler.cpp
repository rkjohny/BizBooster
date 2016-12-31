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


#include "RequestHandler.h"
#include "ApiExecutor.h"
#include "LogFactory.h"
#include "ApiUtils.h"

using namespace Rest;

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
                        jresponse = ApiExecutor::ExecuteSingleApi(request, jrequest);
                    } else if (jrequest.is_array()) {
                        jresponse = ApiExecutor::ExecuteMultipleApi(request, jrequest);
                    } else {
                        jresponse = Api::ApiUtils::BadRequestResponse();
                    }
                } catch (Common::AppException &e) {
                    LOG_ERROR("Failed to handle request with error: " + e.ToString());
                    //jresponse = Api::ApiUtils::ErrorResponse(e.GetCode(), e.GetMessage());
                    jresponse = e.Serialize();
                } catch (std::exception &e) {
                    Common::AppException ex = Common::AppException(e);
                    LOG_ERROR("Failed to handle request with error: " + ex.ToString());
                    //jresponse = Api::ApiUtils::ErrorResponse(ex.GetCode(), ex.GetMessage());
                    jresponse = ex.Serialize();
                }
            })
    .wait();

    LOG_DEBUG("Response: " + jresponse.serialize());

    request.reply(web::http::status_codes::OK, jresponse);
}

void RequestHandler::HandleDeleteRequest(web::http::http_request& request)
{

}
