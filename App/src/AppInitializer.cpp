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

#include "AppInitializer.h"
#include "WAppDef.h"
#include "AppDef.h"
#include "Converter.h"
#include "Common.h"
#include "LogFactory.h"
#include "CFReaderFactory.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "Json.h"
#include "LCrypto.h"

#include <string>

namespace WebApp {

void AppInitializer::Initialize()
{
    // Load all libraries
    Common::LoadLibrary();
    
    // Initializing config reader and reading server config file
    auto server_config_reader =
            Fio::CFReaderFactory::CreateConfigReader(APP_CONFIG_FILE_NAME,
            Fio::ConFigFileType::PROPERTY_FILE);

    server_config_reader->SetFile(APP_CONFIG_FILE_NAME);

    // creating server logger
    auto logger = Fio::LogFactory::GetLogger(APP_LOGGER);

    // Adding file stream to logger
    auto filename = server_config_reader->GetValueOf(APP_LOG_FILE_PATH) +
            PATH_SEPARATOR + server_config_reader->GetValueOf(APP_LOG_FILE_NAME);

    Fio::OFStream* ofStream = new Fio::OFStream();
    ofStream->SetFile(filename);
    logger->AddStream(filename, ofStream);

    auto loglevelStr = server_config_reader->GetValueOf(APP_LOG_LEVEL);
    try {
        logger->SetLogLevel(Common::Converter::ToInt32(loglevelStr));
    } catch (...) {
    }

    // Adding standard output (console) stream
    auto ostdStream = new Fio::OSTDStream();
    logger->AddStream("standard_output_stram", ostdStream);

    /* load rest of libraries*/
    Json::LoadLibrary();
    LCrypto::LoadLibrary();
}


}

