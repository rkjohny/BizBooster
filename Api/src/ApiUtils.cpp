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

namespace Api {

web::json::value ApiUtils::ErrorResponse(AppErrorCode code, const std::string &message)
{
    web::json::value response;
    response[U("error")] = web::json::value::number(static_cast<int>(code));
    response[U("message")] = web::json::value::string(message);
    return response;
}

web::json::value ApiUtils::UnknownErrorResponse()
{
    web::json::value jresponse;
    jresponse[U("error")] = web::json::value::number(AppErrorCode::UN_KNOWN_ERROR);
    jresponse[U("message")] = web::json::value::string(U(UN_KNOWN_ERROR_STR));
    return jresponse;
}

web::json::value ApiUtils::BadRequestResponse()
{
    web::json::value jresponse;
    jresponse[U("error")] = web::json::value::number(AppErrorCode::BAD_REQUEST);
    jresponse[U("message")] = web::json::value::string(U(BAD_REQUEST_STR));
    return jresponse;
}

web::json::value ApiUtils::InternalServerErrorResponse()
{
    web::json::value jresponse;
    jresponse[U("error")] = web::json::value::number(AppErrorCode::INTERNAL_SERVER_ERROR);
    jresponse[U("message")] = web::json::value::string(U(INTERNAL_SERVER_ERROR_STR));
    return jresponse;
}


}