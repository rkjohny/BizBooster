
#ifndef APPFACTORY_H_
#define APPFACTORY_H_

#include "BaseLogger.h"
#include "BasePropertyReader.h"
#include <memory>
#include <map>

#define LOG_DEBUG(message) Common::AppFactory::GetLogger()->Debug(__FILE__, __LINE__, message);
#define LOG_INFO(message) Common::AppFactory::GetLogger()->Info(__FILE__, __LINE__, message);
#define LOG_WARNING(message) Common::AppFactory::GetLogger()->Warning(__FILE__, __LINE__, message);
#define LOG_ERROR(message) Common::AppFactory::GetLogger()->Error(__FILE__, __LINE__, message);


namespace Common {

    enum ConFigFileType
    {
        PROPERTY_FILE,
        XML_FILE
    };

    class AppFactory {
    public:

        class Logger : public BaseLogger {
            friend class AppFactory;
        public:
            ~Logger() = default;

            void Debug(const char *fname, int line, const string &&message);

            void Info(const char *fname, int line, const string &&message);

            void Warning(const char *fname, int line, const string &&message);

            void Error(const char *fname, int line, const string &&message);

        protected:
            Logger() = default;

        private:
            NON_COPY_NON_ASSIGN_ABLE(Logger);
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

        static std::shared_ptr<Logger> GetLogger();
        static void DisposeLogger();

        static std::shared_ptr<ConfigReader> CreateConfigReader(std::string &&key, ConFigFileType type);
        static std::shared_ptr<ConfigReader> GetConfigReader(std::string &&key);
        static bool DisposeConfigReader(std::string &key);
        static void DisposeConfigReader();

    private:
        AppFactory() = delete;
        ~AppFactory() = delete;

        NON_COPY_NON_ASSIGN_ABLE(AppFactory);


        static std::shared_ptr<Logger> cm_logger;

        static std::map<std::string, std::shared_ptr<ConfigReader>> cm_configReaderList;
    };

} /* namespace Common */

#endif /* APPFACTORY_H_ */
