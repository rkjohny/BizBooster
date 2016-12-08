/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of the author (Rezaul Karim)
 *     and is not to be disclosed or used without prior written permission of the author.
 *     This copyrightextends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 */

#ifndef API_EXECUTOR_H
#define API_EXECUTOR_H

#include "ApiCode.h"
#include "BaseInput.h"

#include <cpprest/json.h>

namespace Server {

    class ApiExecutor {
    public:
        static web::json::value ExecuteSingleApi(const web::json::value &jrequest);

        static web::json::value ExecuteMultipleApi(const web::json::value &jrequests);

        static web::json::value BadRequestResponse();

        static web::json::value UnknownErrorResponse();

        static web::json::value InternalServerErrorResponse();
    };


} // namespace Server

#endif // API_EXECUTOR_H
