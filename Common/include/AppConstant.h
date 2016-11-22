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

#define SERVER_LOG_FILE_NAME "TradeXServer.log"
#define SERVER_CONFIG_FILE_NAME "TradeXServer.ini"

#define SERVER_LOG_FILE_PATH_STR "LOG_FILE_PATH"
#define SERVER_LOG_LEVEL_STR "LOG_LEVEL"

#define CLIENT_PROP_FILE_NAME "lang.en_US.properties"
#define CLIENT_PROP_APPLICATION_TITLE "appliction.tilte"

#define CLIENT_VERSION "0.1"

#define CLIENT_LOG_FILE_NAME "TradeXClient.log"
#define CLIENT_CONFIG_FILE_NAME "TradeXClient.ini"

#define CLIENT_LOG_FILE_PATH_STR "LOG_FILE_PATH"
#define CLIENT_LOG_LEVEL_STR "LOG_LEVEL"


#define JSON_API U("@api")
#define JSON_DATA U("@data")


enum ApiReturnCode
{
    SUCCESS = 200,
    UN_KNOWN = -1,
    NOT_IMPLEMENTED = -2,
    COULD_NOT_OPEN_FILE = -3,
    INVALID_ARGUMENT = -4,
    INVALID_REQUEST_DATA = -5
};

enum HttpResposeCode
{
    OK = 200, NOT_FOUND = 404
};

#endif
