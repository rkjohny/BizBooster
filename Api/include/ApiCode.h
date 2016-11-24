#ifndef API_CODE_H
#define API_CODE_H

#include "AppConstant.h"

namespace Api
{


enum ApiCode
{
    ADD_USER = 0,
    REGISTER_USER
};

enum ApiReturnCode
{
    SUCCESS = 200,
    UN_KNOWN = UNKNOWN_ERROR,
    INVALID_REQUEST_DATA = -0x2001
};


}

#endif


