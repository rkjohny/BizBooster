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
#include "StringUtils.h"
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
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (!m_isDisposed) {
        m_properties.clear();
        m_isDisposed = true;
    }
}

void BasePropertyReader::SetFile(const string& filename) noexcept(false)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    m_fileName = filename;
    LoadFile(filename);
    m_isDisposed = false;
}

void BasePropertyReader::ReloadFile() noexcept(false)
{
    boost::lock_guard<boost::mutex> guard(m_mutex);
    LoadFile(m_fileName);
    m_isDisposed = false;
}

void BasePropertyReader::LoadFile(const string& filename) noexcept(false)
{
    try {
        ifstream infs(filename.c_str());
        string line;
        m_properties.clear();

        try {
            while (getline(infs, line)) {
                Common::StringUtils::Trim(line);
                if (line.length() == 0 || line.at(0) == '#') {
                    continue;
                }

                size_t pos = line.find(PAIR_SEPERATOR);
                //pos must be valid index and cannot be the first and last index
                if (pos > 0 && pos < line.size() - 1) {
                    vector< string > listValue = vector< string >();
                    Common::StringUtils::Tokenize(listValue, line, PAIR_SEPERATOR);
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
    boost::lock_guard<boost::mutex> guard(m_mutex);
    if (!m_isDisposed) {
        if (m_properties.find(key) != m_properties.end()) {
            value = m_properties[ key ];
        }
    }    
    return value;
}

} /* namespace Common */
