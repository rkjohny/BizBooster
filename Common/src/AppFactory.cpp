/*
 * AppFactory.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#include "AppFactory.h"

namespace Common {

AppFactory::Logger* AppFactory::cm_logger = nullptr;
AppFactory::PropertyReader* AppFactory::cm_configReader = nullptr;
AppFactory::PropertyReader* AppFactory::cm_propertyReader = nullptr;
std::shared_ptr<AppFactory::PropertyReader> AppFactory::cm_dboConfigReader = nullptr;

AppFactory::Logger* AppFactory::GetLogger()
{
    if (!cm_logger) {
        cm_logger = new AppFactory::Logger();
    }
    return cm_logger;
}

void AppFactory::DisposeLogger()
{
    if (cm_logger) {
        cm_logger->Dispose();
    }
}

AppFactory::PropertyReader* AppFactory::GetConfigReader()
{
    if (!cm_configReader) {
        cm_configReader = new AppFactory::PropertyReader();
    }
    return cm_configReader;
}

void AppFactory::DisposeConfigReader()
{
    if (cm_configReader) {
        cm_configReader->Dispose();
    }
}

AppFactory::PropertyReader* AppFactory::GetPropertyReader()
{
    if (!cm_propertyReader) {
        cm_propertyReader = new AppFactory::PropertyReader();
    }
    return cm_propertyReader;
}

void AppFactory::DisposePropertyReader()
{
    if (cm_propertyReader) {
        cm_propertyReader->Dispose();
    }
}

void AppFactory::Dispose()
{
    DisposeLogger();
    DisposeConfigReader();
    DisposePropertyReader();
}


std::shared_ptr<ConfigReader> AppFactory::GetDboConfigReader()
{
    if (!cm_dboConfigReader) {
        cm_dboConfigReader = std::shared_ptr<AppFactory::PropertyReader>(new AppFactory::PropertyReader());
    }
    return cm_dboConfigReader;
}

void AppFactory::DisposeDboConfigReader()
{
    if(cm_dboConfigReader) {
        cm_dboConfigReader->Dispose();
    }
}

} /* namespace Common */
