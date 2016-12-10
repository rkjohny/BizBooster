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


#include "ServerInitializer.h"
#include "StringUtility.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "AppFactory.h"
#include "Api.h"
#include "Json.h"
#include "Common.h"
#include "ServerConfig.h"
#include "Converter.h"

using namespace std;
using namespace Server;
using namespace Common;
using namespace Api;

void ServerInitializer::Initialize()
{
    // Initializing config reader and reading server config file
    auto server_config_reader = AppFactory::CreateConfigReader(SERVER_CONFIG_FILE_NAME, Common::ConFigFileType::PROPERTY_FILE);
    server_config_reader->SetFile(SERVER_CONFIG_FILE_NAME);

    // creating server logger
    auto logger = AppFactory::GetLogger();

    // Adding file stream to logger
    string filename = server_config_reader->GetValueOf(SERVER_LOG_FILE_PATH_STR) + PATH_SEPARATOR + SERVER_LOG_FILE_NAME;
    OFStream* ofStream = new OFStream();
    ofStream->SetFile(std::string(filename));
    logger->AddStream(std::move(filename), ofStream);

    string&& loglevelStr = server_config_reader->GetValueOf(SERVER_LOG_LEVEL_STR);
    try {
        logger->SetLogLevel(Converter::ToInt32(std::move(loglevelStr)));
    } catch (...) {
    }

    // Adding standard output (console) stream
    OSTDStream *ostdStream = new OSTDStream();
    logger->AddStream("standard_output_stram", ostdStream);

    // Load all libraries
    Common::LoadLibrary();
    Json::LoadLibrary();
    Api::LoadLibrary();

}
