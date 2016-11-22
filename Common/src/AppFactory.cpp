/*
 * AppFactory.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#include "BizBooster/Common/AppFactory.h"

namespace Common
{

AppFactory::Logger* AppFactory::cm_logger = nullptr;
AppFactory::ConfigReader* AppFactory::cm_configReader = nullptr;
AppFactory::ConfigReader* AppFactory::cm_propertyReader = nullptr;

AppFactory::Logger* AppFactory::GetLogger()
{
    if ( !cm_logger )
    {
        cm_logger = new AppFactory::Logger();
    }
    return cm_logger;
}

void AppFactory::DisposeLogger()
{
    if ( cm_logger )
    {
        cm_logger->Dispose();
    }
}

AppFactory::ConfigReader* AppFactory::GetConfigReader()
{
    if ( !cm_configReader )
    {
        cm_configReader = new AppFactory::ConfigReader();
    }
    return cm_configReader;
}

void AppFactory::DisposeConfigReader()
{
    if ( cm_configReader )
    {
        cm_configReader->Dispose();
    }
}

AppFactory::ConfigReader* AppFactory::GetPropertyReader()
{
    if ( !cm_propertyReader )
    {
        cm_propertyReader = new AppFactory::ConfigReader();
    }
    return cm_propertyReader;
}

void AppFactory::DisposePropertyReader()
{
    if ( cm_propertyReader )
    {
        cm_propertyReader->Dispose();
    }
}

void AppFactory::Dispose()
{
    DisposeLogger();
    DisposeConfigReader();
    DisposePropertyReader();
}

} /* namespace Common */
