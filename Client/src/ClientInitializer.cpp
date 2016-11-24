#include "ClientInitializer.h"
#include "ClientConstant.h"
#include "StringUtils.h"
#include "AppFactory.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "AppConstant.h"

#include <string>

using namespace std;
using namespace Client;
using namespace Common;


void ClientInitializer::Initialize()
{
    // Initializing property reader and reading server config file
    AppFactory::ConfigReader* propertyReader = AppFactory::GetPropertyReader();
    propertyReader->SetFile( CLIENT_PROP_FILE_NAME );

    // Initializing config reader and reading server config file
    AppFactory::ConfigReader* configReader = AppFactory::GetConfigReader();
    configReader->SetFile( CLIENT_CONFIG_FILE_NAME );

    // creating client logger
    AppFactory::Logger* logger = AppFactory::GetLogger();

    // Adding file stream
    string filename = configReader->GetValueOf( CLIENT_LOG_FILE_PATH_STR ) + PATH_SEPARATOR + CLIENT_LOG_FILE_NAME;
    OFStream* stream = new OFStream();
    stream->SetFile( filename );
    logger->AddStream( filename, stream );
    string loglevel = CONFIG_VALUE( CLIENT_LOG_LEVEL_STR );
    try
    {
        logger->SetLogLevel( StringUtils::ToInt( loglevel ) );
    }
    catch ( ... ) {}

    // Adding standard output (console) stream
    OSTDStream *ostdStram = new OSTDStream();
    logger->AddStream( "standard_output_stram", ostdStram );
}
