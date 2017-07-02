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

#ifndef API_UTILS_H
#define API_UTILS_H

#include <cpprest/json.h>
#include "AppError.h"
#include "AppCommonDef.h"

namespace Mocxygen {


class ApiUtils {
public:
    MAKE_STATIC(ApiUtils);
    
    static web::json::value ErrorResponse(AppErrorCode code, const std::string &message);

    static web::json::value BadRequestResponse();

    static web::json::value UnknownErrorResponse();

    static web::json::value InternalServerErrorResponse();    
};


}



#endif //API_UTILS_H
