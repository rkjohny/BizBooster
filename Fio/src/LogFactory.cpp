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

#include "LogFactory.h"
#include "FileUtility.h"
#include "Converter.h"

#include <cstdarg>
#include <cpprest/details/SafeInt3.hpp>


namespace Fio {

std::map<std::string, LogFactory::Logger*> LogFactory::cm_loggersList;


void LogFactory::Logger::Debug(const char *fname, int line, const string &&message)
{
    BaseLogger::Debug(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}

void LogFactory::Logger::Info(const char *fname, int line, const string &&message)
{
    BaseLogger::Info(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}

void LogFactory::Logger::Warning(const char *fname, int line, const string &&message)
{
    BaseLogger::Warning(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}

void LogFactory::Logger::Error(const char *fname, int line, const string &&message)
{
    BaseLogger::Error(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), std::move(message));
}


void LogFactory::Logger::Debug(const char *fname, int line, const string &message)
{
    BaseLogger::Debug(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LogFactory::Logger::Info(const char *fname, int line, const string &message)
{
    BaseLogger::Info(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LogFactory::Logger::Warning(const char *fname, int line, const string &message)
{
    BaseLogger::Warning(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LogFactory::Logger::Error(const char *fname, int line, const string &message)
{
    BaseLogger::Error(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), message);
}

void LogFactory::Logger::Debug(const char *fname, int line, const char *format, ...)
{
    char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(dest, (1024 * 16 - 1), format, argptr);
    va_end(argptr);

    BaseLogger::Debug(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LogFactory::Logger::Info(const char *fname, int line, const char *format, ...)
{
    char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(dest, (1024 * 16 - 1), format, argptr);
    va_end(argptr);

    BaseLogger::Info(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LogFactory::Logger::Warning(const char *fname, int line, const char *format, ...)
{
    char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(dest, (1024 * 16 - 1), format, argptr);
    va_end(argptr);

    BaseLogger::Warning(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LogFactory::Logger::Error(const char *fname, int line, const char *format, ...)
{
    char dest[1024 * 16];
    va_list argptr;
    va_start(argptr, format);
    vsnprintf(dest, (1024 * 16 - 1), format, argptr);
    va_end(argptr);

    BaseLogger::Error(Common::FileUtility::GetNameWithoutType(fname) + ":" +
            Common::Converter::ToStr(line), dest);
}

void LogFactory::Dispose()
{
    DisposeLogger();
}

LogFactory::Logger* LogFactory::GetLogger(std::string &&key)
{
    LogFactory::Logger *logger = nullptr;
    
    auto itr = cm_loggersList.find(key);
        
    if (itr != cm_loggersList.end()) {
        logger = itr->second;
    } else {
        logger = new LogFactory::Logger();
        cm_loggersList[std::move(key)] = logger;
    }
    
    return logger;
}

bool LogFactory::DisposeLogger(std::string &key)
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

void LogFactory::DisposeLogger()
{
    for (auto &reader : cm_loggersList) {
        reader.second->Dispose();
        delete reader.second;
    }
    cm_loggersList.clear();
}


} /* namespace Common */
