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


#include "ServiceInitializer.h"
#include "StringUtility.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "CFReaderFactory.h"
#include "LibMocxygen.h"
#include "Json.h"
#include "LibCommon.h"
#include "PantoonDef.h"
#include "Converter.h"
#include "LoggerFactory.h"
#include "LibLogfig.h"
#include "LibCipher.h"
#include <string>

using namespace std;
using namespace Pantoon;
using namespace Common;
using namespace Mocxygen;

void ServiceInitializer::Initialize()
{
    // Initializing config reader and reading server config file
    auto server_config_reader =
            Logfig::CFReaderFactory::CreateConfigReader(SERVICE_CONFIG_FILE_NAME,
            Logfig::ConFigFileType::PROPERTY_FILE);

    server_config_reader->SetFile(SERVICE_CONFIG_FILE_NAME);

    // creating server logger
    auto logger = Logfig::LoggerFactory::GetLogger(APP_LOGGER);

    // Adding file stream to logger
    auto filename = server_config_reader->GetValueOf(SERVICE_LOG_FILE_PATH) +
            PATH_SEPARATOR + server_config_reader->GetValueOf(SERVICE_LOG_FILE_NAME);
    
    auto ofStream = new Logfig::OFStream();
    ofStream->SetFile(filename);
    logger->AddStream(filename, ofStream);

    auto loglevelStr = server_config_reader->GetValueOf(SERVICE_LOG_LEVEL);
    try {
        logger->SetLogLevel(Converter::ToInt32(loglevelStr));
    } catch (...) {
    }

    // Adding standard output (console) stream
    auto ostdStream = new Logfig::OSTDStream();
    logger->AddStream("standard_output_stram", ostdStream);

    // Load all libraries
    Common::LoadLibrary();
    Cipher::LoadLibrary();
    Logfig::LoadLibrary();
    Cmarshal::Json::LoadLibrary();
    Mocxygen::LoadLibrary();
}
