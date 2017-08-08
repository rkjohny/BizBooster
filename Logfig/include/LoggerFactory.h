/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */


#ifndef LOGFIG_LOGGER_FACTORY_H
#define LOGFIG_LOGGER_FACTORY_H

#include "AppCommonDef.h"
#include "BaseLogger.h"
#include "BasePropertyReader.h"
#include <memory>
#include <map>


#define LOG_DEBUG(message) \
    if (Logfig::LoggerFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_DEBUG) \
        Logfig::LoggerFactory::GetLogger(APP_LOGGER)->Debug(__FILE__, __LINE__, message);

#define LOG_INFO(message) \
    if (Logfig::LoggerFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_INFO) \
        Logfig::LoggerFactory::GetLogger(APP_LOGGER)->Info(__FILE__, __LINE__, message);

#define LOG_WARNING(message) \
    if (Logfig::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_WARNING) \
        Logfig::LogFactory::GetLogger(APP_LOGGER)->Warning(__FILE__, __LINE__, message);

#define LOG_ERROR(message) \
    if (Logfig::LoggerFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_ERROR) \
        Logfig::LoggerFactory::GetLogger(APP_LOGGER)->Error(__FILE__, __LINE__, message);


#define FLOG_DEBUG(message, ...) \
    if (Logfig::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_DEBUG) \
        Logfig::LogFactory::GetLogger(APP_LOGGER)->Debug(__FILE__, __LINE__, message, ##__VA_ARGS__);

#define FLOG_INFO(message, ...) \
    if (Logfig::LoggerFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_INFO) \
        Logfig::LoggerFactory::GetLogger(APP_LOGGER)->Info(__FILE__, __LINE__, message, ##__VA_ARGS__);

#define FLOG_WARNING(message, ...) \
    if (Logfig::LogFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_WARNING) \
        Logfig::LogFactory::GetLogger(APP_LOGGER)->Warning(__FILE__, __LINE__, message, ##__VA_ARGS__);

#define FLOG_ERROR(message, ...) \
    if (Logfig::LoggerFactory::GetLogger(APP_LOGGER)->GetLogLevel() >= Logfig::BaseLogger::LogLevel::LOG_LEVEL_ERROR) \
        Logfig::LoggerFactory::GetLogger(APP_LOGGER)->Error(__FILE__, __LINE__, message, ##__VA_ARGS__);


namespace Logfig {

class LoggerFactory {
private:
    MAKE_STATIC(LoggerFactory);
    
public:
    class Logger : public BaseLogger {
        friend class LoggerFactory;
    
    private:
        NON_COPY_NON_MOVE_ABLE(Logger);
        
    public:
        void Debug(const char *fname, int line, const std::string &&message);
        void Info(const char *fname, int line, const std::string &&message);
        void Warning(const char *fname, int line, const std::string &&message);
        void Error(const char *fname, int line, const std::string &&message);
        
        
        void Debug(const char *fname, int line, const std::string &message);
        void Info(const char *fname, int line, const std::string &message);
        void Warning(const char *fname, int line, const std::string &message);
        void Error(const char *fname, int line, const std::string &message);
        

        void Debug(const char *fname, int line, const char *format, ...);
        void Info(const char *fname, int line, const char *format, ...);
        void Warning(const char *fname, int line, const char *format, ...);
        void Error(const char *fname, int line, const char *format, ...);

    protected:
        ~Logger() = default;
        Logger() = default;    
    };

    static void Dispose();
    static Logger* GetLogger(std::string &&key);
    static void DisposeLogger();
    static bool DisposeLogger(std::string &key);
    
private:
    static std::map<std::string, Logger*> cm_loggersList;
};

} /* namespace Logfig */

#endif /* LOGFIG_LOGGER_FACTORY_H */
