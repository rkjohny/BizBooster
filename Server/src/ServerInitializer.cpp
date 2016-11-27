#include "ServerInitializer.h"
#include "ServerConstant.h"
#include "StringUtils.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "AppFactory.h"
#include "AppConstant.h"
#include "Api.h"
#include "Json.h"
#include "Common.h"
#include <string>

using namespace std;
using namespace Server;
using namespace Common;
using namespace Api;

void ServerInitializer::Initialize()
{
    // Load all libraries
    Common::LoadLibrary();
    Json::LoadLibrary();
    Api::LoadLibrary();

    // Initializing config reader and reading server config file
    AppFactory::ConfigReader* configReader = AppFactory::GetConfigReader();
    configReader->SetFile( SERVER_CONFIG_FILE_NAME );

    // creating server logger
    AppFactory::Logger* logger = AppFactory::GetLogger();

    // Adding file stream to logger
    string filename = CONFIG_VALUE( SERVER_LOG_FILE_PATH_STR ) + PATH_SEPARATOR + SERVER_LOG_FILE_NAME;
    filename = AppFactory::GetConfigReader()->GetValueOf( SERVER_LOG_FILE_PATH_STR ) + PATH_SEPARATOR + SERVER_LOG_FILE_NAME;
    OFStream* ofStream = new OFStream();
    ofStream->SetFile( filename );
    logger->AddStream( filename, ofStream );

    string loglevelStr = configReader->GetValueOf( SERVER_LOG_LEVEL_STR );
    try
    {
        logger->SetLogLevel( StringUtils::ToInt( loglevelStr ) );
    }
    catch ( ... ) {}

    // Adding standard output (console) stream
    OSTDStream *ostdStram = new OSTDStream();
    logger->AddStream( "standard_output_stram", ostdStram );
}
