/*
 * TradeXLogger.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#include "BaseLogger.h"
#include "DateTimeUtils.h"
#include "FileUtility.h"

namespace Common {

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
    m_mutex.lock();
    if (!m_isDosposed) {
        auto itr = m_streamList.begin();
        if (itr != m_streamList.end()) {
            if (itr->second) {
                delete itr->second;
            }
            m_streamList.erase(itr);
        }
        m_isDosposed = true;
    }
    m_mutex.unlock();
}

void BaseLogger::SetLogLevel(int level)
{
    if (level >= LOG_LVEL_ERROR && level <= LOG_LEVEL_DEBUG) {
        m_logLevel = level;
    }
}

void BaseLogger::AddStream(const string& key, OStream* ostram)
{
    m_mutex.lock();
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
    m_isDosposed = false;
    m_mutex.unlock();
}

void BaseLogger::RemoveStream(const string& key)
{
    m_mutex.lock();
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
        m_isDosposed = true;
    }
    m_mutex.unlock();
}

void BaseLogger::Debug(const string& fname, const string& message)
{
    if (m_logLevel >= LOG_LEVEL_DEBUG) {
        Write(FileUtility::GetNameWithoutType(fname) + " "
                + DateTimeUtils::GetTimeStamp() + " DEBUG - "
                + message);
    }
}

void BaseLogger::Info(const string& fname, const string& message)
{
    if (m_logLevel >= LOG_LEVEL_INFO) {
        Write(FileUtility::GetNameWithoutType(fname) + " "
                + DateTimeUtils::GetTimeStamp() + " INFO - " + message);
    }
}

void BaseLogger::Warning(const string& fname, const string& message)
{
    if (m_logLevel >= LOG_LEVEL_WARNING) {
        Write(FileUtility::GetNameWithoutType(fname) + " "
                + DateTimeUtils::GetTimeStamp() + " WARNING - "
                + message);
    }
}

void BaseLogger::Error(const string& fname, const string& message)
{
    if (m_logLevel >= LOG_LVEL_ERROR) {
        Write(FileUtility::GetNameWithoutType(fname) + " "
                + DateTimeUtils::GetTimeStamp() + " ERROE - "
                + message);
    }
}

void BaseLogger::Write(const string& message)
{
    m_mutex.lock();
    try {
        if (!m_isDosposed) {
            for (auto& stream : m_streamList) {
                stream.second->Write(message);
            }
        }
    } catch (...) {
    }
    m_mutex.unlock();
}

} /* namespace Common */
