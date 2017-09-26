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

#include "BoostRandGenerator.h"
#include "Converter.h"

namespace Cipher {
#ifdef WINDOWS
    BoostRandGenerator::BoostRandGenerator() : m_boostRandDevice("MS_DEF_PROV") {
    }
#elif defined LINUX
    BoostRandGenerator::BoostRandGenerator() : m_boostRandDevice("/dev/urandom") {
    }
#endif
    
    BoostRandGenerator::~BoostRandGenerator() {
    }

    void BoostRandGenerator::Dispose() {

    }

    bool BoostRandGenerator::Initialize() {
        return false;
    }

    bool BoostRandGenerator::GetRandomBytes(std::vector<uint8_t> &bytes, int length) {
        boost::uint32_t *buffer = new uint32_t[length / 4];

        m_boostRandDevice.generate(buffer, (buffer + length / 4));

        const uint8_t* buff = (const uint8_t*) buffer;

        for (int i = 0; i < length / 2; i++) {
            bytes.push_back(buff[i]);
        }

        delete buffer;
        return true;
    }

    bool BoostRandGenerator::GetRandomBytes(std::string &bytes, int length) {
        boost::uint32_t *buffer = new uint32_t[length / 4];

        m_boostRandDevice.generate(buffer, (buffer + length / 4));
        bytes = Common::Converter::ToHexStr((const uint8_t*) (buffer), length / 2);

        delete buffer;
        return true;
    }

}