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

std::map<std::string, ConfigReader*> CFReaderFactory::cm_configReaderList;

void CFReaderFactory::Dispose()
{
    DisposeConfigReader();
}

ConfigReader* CFReaderFactory::CreateConfigReader(const std::string &key, ConFigFileType type)
{
    ConfigReader* reader = nullptr;

    auto itr = cm_configReaderList.find(key);

    if (itr != cm_configReaderList.end()) {
        reader = itr->second;
    }

    if (!reader) {
        switch (type) {
        case PROPERTY_FILE:
            reader = new PropertyReader();
            break;

        case XML_FILE:
            throw runtime_error("Support of ConFigFileType::XML_FILE not implemented");
        }
        cm_configReaderList[key] = reader;
    }

    return reader;
}

ConfigReader* CFReaderFactory::GetConfigReader(const std::string &key)
{
    auto itr = cm_configReaderList.find(key);
    if (itr != cm_configReaderList.end()) {
        return itr->second;
    }
    return nullptr;
}

bool CFReaderFactory::DisposeConfigReader(const std::string &key)
{
    auto itr = cm_configReaderList.find(key);

    if (itr != cm_configReaderList.end()) {

        itr->second->Dispose();
        cm_configReaderList.erase(itr);

        if (itr->second->GetType() == ConFigFileType::PROPERTY_FILE) {
            delete dynamic_cast<PropertyReader*> (itr->second);
        } else {
            throw runtime_error("Could not delete, ConFigFileType::XML_FILE not implemented");
        }
        return true;
    }
    return false;
}

void CFReaderFactory::DisposeConfigReader()
{
    for (auto &reader : cm_configReaderList) {

        reader.second->Dispose();

        if (reader.second->GetType() == ConFigFileType::PROPERTY_FILE) {
            delete dynamic_cast<PropertyReader*> (reader.second);
        } else {
            throw runtime_error("Could not delete, ConFigFileType::XML_FILE not implemented");
        }
    }
    cm_configReaderList.clear();
}

} /* namespace Common */
