/*
 * AppFactory.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#ifndef APPFACTORY_H_
#define APPFACTORY_H_

#include "BaseLogger.h"
#include "BaseConfigReader.h"

#define LOG_DEBUG(message) AppFactory::GetLogger()->Debug(__FILE__,message);
#define LOG_INFO(message) AppFactory::GetLogger()->Info(__FILE__,message);
#define LOG_WARNING(message) AppFactory::GetLogger()->Warning(__FILE__,message);
#define LOG_ERROR(message) AppFactory::GetLogger()->Error(__FILE__,message);

#define CONFIG_VALUE(key) AppFactory::GetConfigReader()->GetValueOf(key)
#define PROPERTY_VALUE(key) AppFactory::GetPropertyReader()->GetValueOf(key)

namespace Common {

class AppFactory
{
public:
    class Logger: public BaseLogger
    {
        friend class AppFactory;
    protected:
        Logger() = default;
        ~Logger() = default;
    };

    class ConfigReader: public BaseConfigReader
    {
        friend class AppFactory;
    protected:
        ConfigReader() = default;
        ~ConfigReader() = default;
    };

    static void Dispose();

    static Logger* GetLogger();
    static void DisposeLogger();
    static ConfigReader* GetConfigReader();
    static void DisposeConfigReader();
    static ConfigReader* GetPropertyReader();
    static void DisposePropertyReader();

private:
    AppFactory() = delete;
    AppFactory( const AppFactory& ) = delete;
    AppFactory& operator=( const AppFactory& ) = delete;
    ~AppFactory() = delete;

    static Logger* cm_logger;
    static ConfigReader* cm_configReader;
    static ConfigReader* cm_propertyReader;
};

} /* namespace Common */

#endif /* APPFACTORY_H_ */
