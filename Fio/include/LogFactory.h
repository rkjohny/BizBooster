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


#ifndef LOG_FACTORY_H
#define LOG_FACTORY_H

#include "AppDef.h"
#include "BaseLogger.h"
#include "BasePropertyReader.h"
#include <memory>
#include <map>


#define LOG_DEBUG(message) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_DEBUG) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Debug(__FILE__, __LINE__, message);

#define LOG_INFO(message) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_INFO) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Info(__FILE__, __LINE__, message);

#define LOG_WARNING(message) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_WARNING) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Warning(__FILE__, __LINE__, message);

#define LOG_ERROR(message) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_ERROR) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Error(__FILE__, __LINE__, message);


#define FLOG_DEBUG(message, ...) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_DEBUG) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Debug(__FILE__, __LINE__, message, ##__VA_ARGS__);

#define FLOG_INFO(message, ...) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_INFO) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Info(__FILE__, __LINE__, message, ##__VA_ARGS__);

#define FLOG_WARNING(message, ...) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_WARNING) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Warning(__FILE__, __LINE__, message, ##__VA_ARGS__);

#define FLOG_ERROR(message, ...) \
    if (Fio::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Fio::BaseLogger::LogLevel::LOG_LEVEL_ERROR) \
        Fio::LogFactory::GetLogger(APP_LOGGER)->Error(__FILE__, __LINE__, message, ##__VA_ARGS__);


namespace Fio {


class LogFactory {
public:
    class Logger : public BaseLogger {
        friend class LogFactory;
    public:
        ~Logger() = default;

        void Debug(const char *fname, int line, const string &&message);
        void Info(const char *fname, int line, const string &&message);
        void Warning(const char *fname, int line, const string &&message);
        void Error(const char *fname, int line, const string &&message);
        
        
        void Debug(const char *fname, int line, const string &message);
        void Info(const char *fname, int line, const string &message);
        void Warning(const char *fname, int line, const string &message);
        void Error(const char *fname, int line, const string &message);
        

        void Debug(const char *fname, int line, const char *format, ...);
        void Info(const char *fname, int line, const char *format, ...);
        void Warning(const char *fname, int line, const char *format, ...);
        void Error(const char *fname, int line, const char *format, ...);

    protected:
        Logger() = default;

    private:
        NON_COPY_NON_MOVE_ABLE(Logger);
    };

    static void Dispose();
    static std::shared_ptr<Logger> GetLogger(std::string &&key);
    static void DisposeLogger();
    static bool DisposeLogger(std::string &key);

private:
    MAKE_STATIC(LogFactory);
    
    static std::map<std::string, std::shared_ptr<Logger>> cm_loggersList;
};

} /* namespace Fio */

#endif /* LOG_FACTORY_H */
