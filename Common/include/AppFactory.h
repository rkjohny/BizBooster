/*
 * AppFactory.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#ifndef APPFACTORY_H_
#define APPFACTORY_H_

#include "BaseLogger.h"
#include "BasePropertyReader.h"
#include <memory>


#define LOG_DEBUG(message) Common::AppFactory::GetLogger()->Debug(__FILE__,message);
#define LOG_INFO(message) Common::AppFactory::GetLogger()->Info(__FILE__,message);
#define LOG_WARNING(message) Common::AppFactory::GetLogger()->Warning(__FILE__,message);
#define LOG_ERROR(message) Common::AppFactory::GetLogger()->Error(__FILE__,message);

#define CONFIG_VALUE(key) Common::AppFactory::GetConfigReader()->GetValueOf(key)
#define PROPERTY_VALUE(key) Common::AppFactory::GetPropertyReader()->GetValueOf(key)

namespace Common {

    class AppFactory {
    public:

        class Logger : public BaseLogger {
            friend class AppFactory;
        protected:
            Logger() = default;
            ~Logger() = default;
        };

        class PropertyReader : public BasePropertyReader {
            friend class AppFactory;

        public:
            ~PropertyReader() = default;

        protected:
            PropertyReader() = default;

            NON_COPY_NON_ASSIGN_ABLE(PropertyReader);
        };

        static void Dispose();

        static Logger* GetLogger();
        static void DisposeLogger();
        static PropertyReader* GetConfigReader();
        static void DisposeConfigReader();
        static PropertyReader* GetPropertyReader();
        static void DisposePropertyReader();

        static std::shared_ptr<ConfigReader> GetDboConfigReader();
        static void DisposeDboConfigReader();

    private:
        AppFactory() = delete;
        AppFactory(const AppFactory&) = delete;
        AppFactory& operator=(const AppFactory&) = delete;
        ~AppFactory() = delete;

        static Logger* cm_logger;
        static PropertyReader* cm_configReader;
        static PropertyReader* cm_propertyReader;

        static std::shared_ptr<PropertyReader> cm_dboConfigReader;
    };

} /* namespace Common */

#endif /* APPFACTORY_H_ */
