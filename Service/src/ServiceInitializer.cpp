/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */


#include "ServiceInitializer.h"
#include "StringUtility.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "CFReaderFactory.h"
#include "Api.h"
#include "Json.h"
#include "Common.h"
#include "ServiceDef.h"
#include "Converter.h"
#include "LogFactory.h"
#include "Fio.h"
#include "LCrypto.h"
#include <string>

using namespace std;
using namespace Rest;
using namespace Common;
using namespace Api;

void ServiceInitializer::Initialize()
{
    // Initializing config reader and reading server config file
    auto server_config_reader =
            Fio::CFReaderFactory::CreateConfigReader(SERVICE_CONFIG_FILE_NAME,
            Fio::ConFigFileType::PROPERTY_FILE);

    server_config_reader->SetFile(SERVICE_CONFIG_FILE_NAME);

    // creating server logger
    auto logger = Fio::LogFactory::GetLogger(APP_LOGGER);

    // Adding file stream to logger
    std::string filename = server_config_reader->GetValueOf(SERVICE_LOG_FILE_PATH) +
            PATH_SEPARATOR + server_config_reader->GetValueOf(SERVICE_LOG_FILE_NAME);
    
    Fio::OFStream* ofStream = new Fio::OFStream();
    ofStream->SetFile(filename);
    logger->AddStream(filename, ofStream);

    std::string&& loglevelStr = server_config_reader->GetValueOf(SERVICE_LOG_LEVEL);
    try {
        logger->SetLogLevel(Converter::ToInt32(loglevelStr));
    } catch (...) {
    }

    // Adding standard output (console) stream
    Fio::OSTDStream *ostdStream = new Fio::OSTDStream();
    logger->AddStream("standard_output_stram", ostdStream);

    // Load all libraries
    Common::LoadLibrary();
    LCrypto::LoadLibrary();
    Fio::LoadLibrary();
    Json::LoadLibrary();
    Api::LoadLibrary();
}
