#include "ClientInitializer.h"
#include "StringUtility.h"
#include "AppFactory.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "CilentConfig.h"

using namespace std;
using namespace Client;
using namespace Common;

void ClientInitializer::Initialize()
{
    // Initializing property reader and reading server config file
    auto propertyReader = AppFactory::CreateConfigReader(LANG_PROP_FILE_NAME, ConFigFileType::PROPERTY_FILE);
    propertyReader->SetFile(LANG_PROP_FILE_NAME);

    auto configReader = AppFactory::CreateConfigReader(CLIENT_CONFIG_FILE_NAME,
                                                         Common::ConFigFileType::PROPERTY_FILE);
    configReader->SetFile(CLIENT_CONFIG_FILE_NAME);

    // creating client logger
    auto logger = AppFactory::GetLogger();

    // Adding file stream
    string filename = configReader->GetValueOf(CLIENT_LOG_FILE_PATH_STR) + PATH_SEPARATOR + CLIENT_LOG_FILE_NAME;
    OFStream *stream = new OFStream();
    stream->SetFile(std::string(filename));
    logger->AddStream(std::move(filename), stream);
    string loglevel = configReader->GetValueOf(CLIENT_LOG_LEVEL_STR);
    try {
        logger->SetLogLevel(StringUtility::ToInt(loglevel));
    } catch (...) {
    }

    // Adding standard output (console) stream
    OSTDStream *ostdStream = new OSTDStream();
    logger->AddStream("standard_output_stram", ostdStream);
}
