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


#include "RequestHandler.h"
#include "ApiExecutor.h"
#include "LoggerFactory.h"
#include "ApiUtils.h"

namespace Pantoon {

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
                        jresponse = Mocxygen::ApiUtils::BadRequestResponse();
                    }
                } catch (Common::AppException &e) {
                    jresponse = e.Serialize();
                    LOG_ERROR("Failed to handle request with error: " + jresponse.serialize());                    
                } catch (std::exception &e) {
                    Common::AppException ex = Common::AppException(e);
                    jresponse = ex.Serialize();
                    LOG_ERROR("Failed to handle request with error: " + jresponse.serialize());                    
                }
            })
    .wait();

    LOG_DEBUG("Response: " + jresponse.serialize());

    request.reply(web::http::status_codes::OK, jresponse);
}

void RequestHandler::HandleDeleteRequest(web::http::http_request& request)
{

}

}