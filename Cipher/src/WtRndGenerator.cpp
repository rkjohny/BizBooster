
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

#include "WtRndGenerator.h"

namespace Cipher {

    WtRndGenerator::WtRndGenerator() {

    }

    WtRndGenerator::~WtRndGenerator() {

    }

    void WtRndGenerator::Dispose() {
        if (!m_isDisposed) {
            m_isDisposed = true;
        }
    }

    bool WtRndGenerator::Initialize() {
        if (!m_isInitialized) {
            m_isInitialized = true;
        }
        return m_isInitialized;
    }

    bool WtRndGenerator::GetRandomBytes(std::vector<uint8_t> &bytes, int length) {
        std::string randStr = m_wtRanGenerator.generateId(length/2);
        const char * buff = randStr.c_str();
        for (size_t i = 0; i<randStr.length(); i++) {
            bytes.push_back(static_cast<uint8_t>(buff[i]));
        }
        return true;
    }

    bool WtRndGenerator::GetRandomBytes(std::string &bytes, int length) {
        bytes = m_wtRanGenerator.generateId(length);
        return true;
    }

    std::string WtRndGenerator::GetRandomBytes(int length) {
        return m_wtRanGenerator.generateId(length);
    }

}