
#ifndef API_UTILS_H
#define API_UTILS_H

#include <cpprest/json.h>
#include "AppError.h"

namespace Api {


class ApiUtils {
public:
    static web::json::value ErrorResponse(AppErrorCode code, const std::string &message);

    static web::json::value BadRequestResponse();

    static web::json::value UnknownErrorResponse();

    static web::json::value InternalServerErrorResponse();
};


}



#endif //API_UTILS_H
