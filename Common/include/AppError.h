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

#ifndef APP_ERROR_H
#define APP_ERROR_H

//#define SUCCESS_STR "Success"
//#define BAD_REQUEST_STR "Bad request."
//#define UN_KNOWN_ERROR_STR "Unknown error."
//#define INTERNAL_SERVER_ERROR_STR "Internal server error."

enum AppErrorCode {
    SUCCESS = 0x0000,
    UN_KNOWN_ERROR = 1,
    NOT_IMPLEMENTED = 2,
    COULD_NOT_OPEN_FILE = 3,
    INVALID_ARGUMENT = 4,
    BAD_REQUEST = 5,
    INTERNAL_SERVER_ERROR = 6,
    DB_OPERATION_FAILED = 7,
    USER_ALREADY_EXISTS = 8,
    UNAUTHORIZED = 9,
    INSIFFICIENT_PRIVILEGE = 10,
    USER_NOT_FOUND = 11,
    AUTHTICATION_FAILURE = 12,
    NOT_SUPPORTED = 13
};


#endif //APP_ERROR_H
