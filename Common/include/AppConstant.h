#ifndef APPCONOSTANT_H
#define APPCONOSTANT_H

#if defined(WIN32) || defined(_WIN32) || defined (__CYGWIN__)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#define FILE_TYPE_SEPERATOR "."

#define STATIC

#define PAIR_SEPERATOR "="

#define SERVER_VERSION = "0.1"

#define SERVER_ADDRESS "http://localhost"
#define SERVER_PORT "8088"

#define SERVER_LOG_FILE_NAME "Server.log"
#define SERVER_CONFIG_FILE_NAME "Server.ini"

#define SERVER_LOG_FILE_PATH_STR "LOG_FILE_PATH"
#define SERVER_LOG_LEVEL_STR "LOG_LEVEL"

#define CLIENT_PROP_FILE_NAME "lang.en_US.properties"
#define CLIENT_PROP_APPLICATION_TITLE "appliction.tilte"

#define CLIENT_VERSION "0.1"

#define CLIENT_LOG_FILE_NAME "Client.log"
#define CLIENT_CONFIG_FILE_NAME "Client.ini"

#define CLIENT_LOG_FILE_PATH_STR "LOG_FILE_PATH"
#define CLIENT_LOG_LEVEL_STR "LOG_LEVEL"


#define JSON_API U("@api")
#define JSON_DATA U("@data")


#define UNKNOWN_ERROR -0x1000

enum AppErrorCode
{
    UN_KNOWN = UNKNOWN_ERROR,
    NOT_IMPLEMENTED = -0x1001,
    COULD_NOT_OPEN_FILE = -0x1002,
    INVALID_ARGUMENT = -0x1003
};

#endif
