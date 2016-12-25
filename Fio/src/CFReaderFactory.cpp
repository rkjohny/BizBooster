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

#include "FileUtility.h"
#include "CFReaderFactory.h"
#include "Converter.h"

#include <cstdarg>

namespace Fio {

std::map<std::string, std::shared_ptr<ConfigReader>> CFReaderFactory::cm_configReaderList;

void CFReaderFactory::Dispose()
{
    DisposeConfigReader();
}

std::shared_ptr<ConfigReader> CFReaderFactory::CreateConfigReader(std::string &&key, ConFigFileType type)
{
    std::shared_ptr<ConfigReader> reader;

    switch (type) {
    case PROPERTY_FILE:
        reader = std::shared_ptr<PropertyReader>(new PropertyReader());
        break;

    case XML_FILE:
        throw runtime_error("Support of ConFigFileType::XML_FILE not implemented");
    }
    cm_configReaderList[std::move(key)] = reader;

    return reader;
}

std::shared_ptr<ConfigReader> CFReaderFactory::GetConfigReader(std::string &&key)
{
    auto itr = cm_configReaderList.find(std::move(key));
    if (itr != cm_configReaderList.end()) {
        return itr->second;
    }
    return nullptr;
}

bool CFReaderFactory::DisposeConfigReader(std::string &key)
{
    auto itr = cm_configReaderList.find(key);
    if (itr != cm_configReaderList.end()) {
        itr->second->Dispose();
        return true;
    }
    return false;
}

void CFReaderFactory::DisposeConfigReader()
{
    for (auto &reader : cm_configReaderList) {
        reader.second->Dispose();
    }
}

} /* namespace Common */
