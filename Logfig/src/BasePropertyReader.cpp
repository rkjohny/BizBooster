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

#include <fstream>
#include "BasePropertyReader.h"
#include "StringUtility.h"
#include "AppCommonDef.h"

namespace Logfig {

BasePropertyReader::BasePropertyReader() : ConfigReader(ConFigFileType::PROPERTY_FILE)
{
}

BasePropertyReader::~BasePropertyReader()
{
    BasePropertyReader::Dispose();
}

void BasePropertyReader::Dispose()
{
    m_mutex.lock();
    if (!m_isDosposed) {
        m_properties.clear();
        m_isDosposed = true;
    }
    m_mutex.unlock();
}

void BasePropertyReader::SetFile(const string& filename) noexcept(false)
{
    m_mutex.lock();
    m_fileName = filename;
    LoadFile(filename);
    m_isDosposed = false;
    m_mutex.unlock();
}

void BasePropertyReader::ReloadFile() noexcept(false)
{
    m_mutex.lock();
    LoadFile(m_fileName);
    m_isDosposed = false;
    m_mutex.unlock();
}

void BasePropertyReader::LoadFile(const string& filename) noexcept(false)
{
    try {
        ifstream infs(filename.c_str());
        string line;
        m_properties.clear();

        try {
            while (getline(infs, line)) {
                line = Common::StringUtility::Trim(line);
                if (line.length() == 0 || line.at(0) == '#') {
                    continue;
                }

                size_t pos = line.find(PAIR_SEPERATOR);
                //pos must be valid index and cannot be the first and last index
                if (pos > 0 && pos < line.size() - 1) {
                    vector< string > listValue = vector< string >();
                    Common::StringUtility::Tokenize(listValue, line, PAIR_SEPERATOR, 2);
                    if (listValue.size() >= 2) {
                        m_properties[ listValue[ 0 ] ] = listValue[ 1 ];
                    }
                }
            }
        } catch (exception &e) {
            infs.close();
            throw Common::AppException(e, AppErrorCode::COULD_NOT_OPEN_FILE,
                    "Could not open file : " + filename);
        }
        infs.close();
    } catch (exception &e) {
        throw Common::AppException(e, AppErrorCode::COULD_NOT_OPEN_FILE,
                "Could not open file : " + filename);
    }
}

string BasePropertyReader::GetValueOf(const string& key)
{
    string value = "";
    m_mutex.lock();
    if (!m_isDosposed) {
        if (m_properties.find(key) != m_properties.end()) {
            value = m_properties[ key ];
        }
    }
    m_mutex.unlock();
    return value;
}

} /* namespace Common */
