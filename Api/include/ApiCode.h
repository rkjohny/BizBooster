#ifndef API_CODE_H
#define API_CODE_H

#include "AppConstant.h"

namespace Api {

#define BAD_REQUEST_STR "Bad request."
#define UN_KNOWN_ERROR_STR "Unknown error."
#define INTERNAL_SERVER_ERROR_STR "Internal server error."

enum ApiReturnCode {
    SUCCESS = 0x0000,
    UN_KNOWN_ERROR = 0x1001,
    BAD_REQUEST = 0x1002,
    INTERNAL_SERVER_ERROR = 0x2001
};


}

#endif


