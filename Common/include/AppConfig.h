#ifndef APPCONOSTANT_H
#define APPCONOSTANT_H

#if defined(WIN32) || defined(_WIN32) || defined (__CYGWIN__)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#define PAIR_SEPERATOR "="

#define FILE_TYPE_SEPERATOR "."

#define JSON_API U("@api")
#define JSON_DATA U("@data")


#define UNKNOWN_ERROR -0x1000

enum AppErrorCode {
    UN_KNOWN = UNKNOWN_ERROR,
    NOT_IMPLEMENTED = -0x1001,
    COULD_NOT_OPEN_FILE = -0x1002,
    INVALID_ARGUMENT = -0x1003
};

#endif
