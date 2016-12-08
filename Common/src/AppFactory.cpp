/*
 * AppFactory.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#include "FileUtility.h"
#include "AppFactory.h"
#include "Converter.h"

namespace Common {

std::shared_ptr<AppFactory::Logger> AppFactory::cm_logger = nullptr;
std::map<std::string, std::shared_ptr<ConfigReader>> AppFactory::cm_configReaderList;


void AppFactory::Logger::Debug(const char *fname, int line, const string &&message)
{
    BaseLogger::Debug(FileUtility::GetNameWithoutType(fname)+ ":" + Converter::ToStr(line), std::move(message));
}


void AppFactory::Logger::Info(const char *fname, int line, const string &&message)
{
    BaseLogger::Info(FileUtility::GetNameWithoutType(fname)+ ":" + Converter::ToStr(line), std::move(message));
}

void AppFactory::Logger::Warning(const char *fname, int line, const string &&message)
{
    BaseLogger::Warning(FileUtility::GetNameWithoutType(fname)+ ":" + Converter::ToStr(line), std::move(message));
}

void AppFactory::Logger::Error(const char *fname, int line, const string &&message)
{
    BaseLogger::Error(FileUtility::GetNameWithoutType(fname)+ ":" + Converter::ToStr(line), std::move(message));
}


void AppFactory::Dispose()
{
    DisposeLogger();
    DisposeConfigReader();
}


std::shared_ptr<AppFactory::Logger> AppFactory::GetLogger()
{
    if (!cm_logger) {
        cm_logger = std::shared_ptr<Logger>(new AppFactory::Logger());
    }
    return cm_logger;
}

void AppFactory::DisposeLogger()
{
    if (cm_logger) {
        cm_logger->Dispose();
    }
}

std::shared_ptr<ConfigReader> AppFactory::CreateConfigReader(std::string &&key, ConFigFileType type)
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

std::shared_ptr<ConfigReader> AppFactory::GetConfigReader(std::string &&key)
{
    auto itr = cm_configReaderList.find(std::move(key));
    if (itr != cm_configReaderList.end()) {
        return itr->second;
    }
    return nullptr;
}

bool AppFactory::DisposeConfigReader(std::string &key)
{
    auto itr = cm_configReaderList.find(key);
    if (itr != cm_configReaderList.end()) {
        itr->second->Dispose();
        return true;
    }
    return false;
}

void AppFactory::DisposeConfigReader()
{
    for (auto &reader : cm_configReaderList) {
        reader.second->Dispose();
    }
}

} /* namespace Common */
