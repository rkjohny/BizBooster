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

#include <Converter.h>
#include "ClientInitializer.h"
#include "StringUtility.h"
#include "CFReaderFactory.h"
#include "OFStream.h"
#include "OSTDStream.h"
#include "CilentDef.h"
#include "Converter.h"
#include "LogFactory.h"


using namespace std;
using namespace Client;
using namespace Common;
using namespace Fio;

void ClientInitializer::Initialize()
{
    // Initializing property reader and reading server config file
    auto propertyReader = Fio::CFReaderFactory::CreateConfigReader(LANG_PROP_FILE_NAME, ConFigFileType::PROPERTY_FILE);
    propertyReader->SetFile(LANG_PROP_FILE_NAME);

    auto configReader = Fio::CFReaderFactory::CreateConfigReader(CLIENT_CONFIG_FILE_NAME,
                                                         Fio::ConFigFileType::PROPERTY_FILE);
    configReader->SetFile(CLIENT_CONFIG_FILE_NAME);

    // creating client logger
    auto logger = LogFactory::GetLogger();

    // Adding file stream
    string filename = configReader->GetValueOf(CLIENT_LOG_FILE_PATH_STR) + PATH_SEPARATOR + CLIENT_LOG_FILE_NAME;
    OFStream *stream = new OFStream();
    stream->SetFile(std::string(filename));
    logger->AddStream(filename, stream);
    string &&loglevel = configReader->GetValueOf(CLIENT_LOG_LEVEL_STR);
    try {
        logger->SetLogLevel(Common::Converter::ToInt32(loglevel));
    } catch (...) {
    }

    // Adding standard output (console) stream
    OSTDStream *ostdStream = new OSTDStream();
    logger->AddStream("standard_output_stram", ostdStream);
}
