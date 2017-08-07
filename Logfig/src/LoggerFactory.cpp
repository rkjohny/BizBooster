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

#include "LoggerFactory.h"
#include "FileUtils.h"
#include "Converter.h"
#include "LogfigDef.h"

#include <cstdarg>


namespace Logfig {

std::map<std::string, LoggerFactory::Logger*> LoggerFactory::cm_loggersList;


void LoggerFactory::Logger::Debug(const char *fname, int line, const string &&message)
{
    BaseLogger::Debug(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}

void LoggerFactory::Logger::Info(const char *fname, int line, const string &&message)
{
    BaseLogger::Info(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}

void LoggerFactory::Logger::Warning(const char *fname, int line, const string &&message)
{
    BaseLogger::Warning(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}

void LoggerFactory::Logger::Error(const char *fname, int line, const string &&message)
{
    BaseLogger::Error(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}


void LoggerFactory::Logger::Debug(const char *fname, int line, const string &message)
{
    BaseLogger::Debug(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LoggerFactory::Logger::Info(const char *fname, int line, const string &message)
{
    BaseLogger::Info(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LoggerFactory::Logger::Warning(const char *fname, int line, const string &message)
{
    BaseLogger::Warning(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LoggerFactory::Logger::Error(const char *fname, int line, const string &message)
{
    BaseLogger::Error(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LoggerFactory::Logger::Debug(const char *fname, int line, const char *format, ...)
{
    char dest[MAX_SIZE_FORMATTED_LOG_MESSAGE];
    
    va_list argptr;
    va_start(argptr, format);
    
    vsnprintf(dest, (MAX_SIZE_FORMATTED_LOG_MESSAGE - 1), format, argptr);
    
    va_end(argptr);

    BaseLogger::Debug(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LoggerFactory::Logger::Info(const char *fname, int line, const char *format, ...)
{
    char dest[MAX_SIZE_FORMATTED_LOG_MESSAGE];
    
    va_list argptr;
    va_start(argptr, format);
    
    vsnprintf(dest, (MAX_SIZE_FORMATTED_LOG_MESSAGE - 1), format, argptr);
    
    va_end(argptr);

    BaseLogger::Info(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LoggerFactory::Logger::Warning(const char *fname, int line, const char *format, ...)
{
    char dest[MAX_SIZE_FORMATTED_LOG_MESSAGE];
    
    va_list argptr;
    va_start(argptr, format);

    vsnprintf(dest, (MAX_SIZE_FORMATTED_LOG_MESSAGE - 1), format, argptr);

    va_end(argptr);

    BaseLogger::Warning(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LoggerFactory::Logger::Error(const char *fname, int line, const char *format, ...)
{
    char dest[MAX_SIZE_FORMATTED_LOG_MESSAGE];
    
    va_list argptr;
    va_start(argptr, format);
    
    vsnprintf(dest, (MAX_SIZE_FORMATTED_LOG_MESSAGE - 1), format, argptr);
    
    va_end(argptr);

    BaseLogger::Error(Common::FileUtils::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LoggerFactory::Dispose()
{
    DisposeLogger();
}

LoggerFactory::Logger* LoggerFactory::GetLogger(std::string &&key)
{
    LoggerFactory::Logger *logger = nullptr;
    
    auto itr = cm_loggersList.find(key);
        
    if (itr != cm_loggersList.end()) {
        logger = itr->second;
    } else {
        logger = new LoggerFactory::Logger();
        cm_loggersList[std::move(key)] = logger;
    }
    
    return logger;
}

bool LoggerFactory::DisposeLogger(std::string &key)
{
    auto itr = cm_loggersList.find(key);
    if (itr != cm_loggersList.end()) {
        itr->second->Dispose();
        cm_loggersList.erase(itr);
        delete itr->second;
        return true;
    }
    return false;
}

void LoggerFactory::DisposeLogger()
{
    for (auto &reader : cm_loggersList) {
        reader.second->Dispose();
        delete reader.second;
    }
    cm_loggersList.clear();
}


} /* namespace Common */
