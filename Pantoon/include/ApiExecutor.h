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

#ifndef API_EXECUTOR_H
#define API_EXECUTOR_H

#include "AbstractBaseInput.h"

#include <cpprest/json.h>
#include "cpprest/http_listener.h"

namespace Pantoon {

    class ApiExecutor {
    private:
        MAKE_STATIC(ApiExecutor);
        
    public:
        static web::json::value ExecuteSingleApi(const web::http::http_request& request, const web::json::value &jrequest);

        static web::json::value ExecuteMultipleApi(const web::http::http_request& request, const web::json::value &jrequests);
    };


} // namespace Server

#endif // API_EXECUTOR_H
