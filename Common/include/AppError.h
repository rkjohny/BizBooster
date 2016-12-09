//
// Created by rezaul on 12/9/16.
//

#ifndef APP_ERROR_H
#define APP_ERROR_H

#define SUCCESS_STR "Success"
#define BAD_REQUEST_STR "Bad request."
#define UN_KNOWN_ERROR_STR "Unknown error."
#define INTERNAL_SERVER_ERROR_STR "Internal server error."

enum AppErrorCode {
    SUCCESS = 0x0000,
    UN_KNOWN_ERROR = 0x0001,
    NOT_IMPLEMENTED = 0x0002,
    COULD_NOT_OPEN_FILE = 0x0003,
    INVALID_ARGUMENT = 0x0004,
    BAD_REQUEST = 0x0005,
    INTERNAL_SERVER_ERROR = 0x0006
};


#endif //APP_ERROR_H