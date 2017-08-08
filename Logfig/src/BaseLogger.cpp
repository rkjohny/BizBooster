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

#include "BaseLogger.h"
#include "DateTimeUtils.h"
#include "FileUtils.h"

namespace Logfig {

BaseLogger::BaseLogger()
{
    m_logLevel = LOG_LEVEL_DEBUG;
}

BaseLogger::~BaseLogger()
{
    BaseLogger::Dispose();
}

void BaseLogger::Dispose()
{
    // user who built the list must call destructor to delete the list
    // make sure m_mutex will be destructed after streamList
    // thats why we declared m_mutex before streamList    
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (!m_isDisposed) {
        auto itr = m_streamList.begin();
        if (itr != m_streamList.end()) {
            if (itr->second) {
                delete itr->second;
            }
            m_streamList.erase(itr);
        }
        m_isDisposed = true;
    }
}

void BaseLogger::SetLogLevel(int level)
{
    if (level >= LOG_LEVEL_ERROR && level <= LOG_LEVEL_DEBUG) {
        m_logLevel = level;
    }
}

void BaseLogger::AddStream(const std::string &key, OStream* ostram)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    auto itr = m_streamList.find(key);
    if (itr != m_streamList.end()) {
        // deleting, otherwise caller will not be able to delete it
        // since we are not returning itr->second
        if (itr->second) {
            delete itr->second;
        }
        m_streamList.erase(itr);
    }
    m_streamList[key] = ostram;
    m_isDisposed = false;
}

void BaseLogger::RemoveStream(const std::string &key)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    auto itr = m_streamList.find(key);
    if (itr != m_streamList.end()) {
        // deleting, otherwise caller will not be able to delete it
        // since we are not returning itr->second
        if (itr->second) {
            delete itr->second;
        }
        m_streamList.erase(itr);
    }
    if (m_streamList.size() == 0) {
        m_isDisposed = true;
    }
}

void BaseLogger::Debug(const std::string&& prefix, const std::string&& message)
{
    if (m_logLevel >= LOG_LEVEL_DEBUG) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " DEBUG - " + std::move(message));
    }
}

void BaseLogger::Info(const std::string&& prefix, const std::string&& message)
{
    if (m_logLevel >= LOG_LEVEL_INFO) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " INFO - " + std::move(message));
    }
}

void BaseLogger::Warning(const std::string&& prefix, const std::string&& message)
{
    if (m_logLevel >= LOG_LEVEL_WARNING) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " WARNING - " + std::move(message));
    }
}

void BaseLogger::Error(const std::string&& prefix, const std::string&& message)
{
    if (m_logLevel >= LOG_LEVEL_ERROR) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " ERROE - " + std::move(message));
    }
}

void BaseLogger::Debug(const std::string&& prefix, const std::string& message)
{
    if (m_logLevel >= LOG_LEVEL_DEBUG) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " DEBUG - " + message);
    }
}

void BaseLogger::Info(const std::string&& prefix, const std::string& message)
{
    if (m_logLevel >= LOG_LEVEL_INFO) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " INFO - " + message);
    }
}

void BaseLogger::Warning(const std::string&& prefix, const std::string& message)
{
    if (m_logLevel >= LOG_LEVEL_WARNING) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " WARNING - " + message);
    }
}

void BaseLogger::Error(const std::string&& prefix, const std::string& message)
{
    if (m_logLevel >= LOG_LEVEL_ERROR) {
        Write(prefix + " " + Common::DateTimeUtils::GetTimeStamp() + 
                " ERROE - " + message);
    }
}

void BaseLogger::Write(const std::string&& message)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    try {
        if (!m_isDisposed) {
            for (auto& stream : m_streamList) {
                stream.second->Write(std::move(message));
            }
        }
    } catch (...) {
    }
}

void BaseLogger::Write(const std::string& message)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    try {
        if (!m_isDisposed) {
            for (auto& stream : m_streamList) {
                stream.second->Write(message);
            }
        }
    } catch (...) {
    }
}

int BaseLogger::GetLogLevel()
{
    return m_logLevel;
}

} /* namespace Common */
