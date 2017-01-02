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

#include "ApiUtils.h"
#include "AppError.h"

namespace Api {

web::json::value ApiUtils::ErrorResponse(AppErrorCode code, const std::string &message)
{
    auto response = web::json::value::object();
    auto error = web::json::value::object();
    error[U("code")] = web::json::value::number(static_cast<int>(code));
    error[U("message")] = web::json::value::string(message);
    response[U("error")] = error;
    return response;
}

web::json::value ApiUtils::UnknownErrorResponse()
{
    auto response = web::json::value::object();
    auto error = web::json::value::object();
    error[U("code")] = web::json::value::number(AppErrorCode::UN_KNOWN_ERROR);
    error[U("message")] = web::json::value::string(U("Unknown error."));
    response[U("error")] = error;
    return response;
}

web::json::value ApiUtils::BadRequestResponse()
{
    auto response = web::json::value::object();
    auto error = web::json::value::object();
    error[U("code")] = web::json::value::number(AppErrorCode::BAD_REQUEST);
    error[U("message")] = web::json::value::string(U("Bad request"));
    response[U("error")] = error;
    return response;
}

web::json::value ApiUtils::InternalServerErrorResponse()
{
    auto response = web::json::value::object();
    auto error = web::json::value::object();
    error[U("code")] = web::json::value::number(AppErrorCode::INTERNAL_SERVER_ERROR);
    error[U("message")] = web::json::value::string(U("Internal server error."));
    response[U("error")] = error;
    return response;
}


}