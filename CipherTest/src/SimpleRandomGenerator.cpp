/*
 * Author: Rezaul Karm
 * Email: rkjohny@gmail.com
 * Creation Date: 11/04/2017
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#include <iostream>
#include <gtest/gtest.h>
#include "SingleTon.h"
#include "BoostRandGenerator.h"
#include "CipherDef.h"
#include "OsslHwRandGenerator.h"
#include "Converter.h"

namespace CipherTest {
    
    TEST(SimpleRandomGenerator, GenerateSimpleBuff) {
#if defined BOOST_RANDOM_ENGINE
        auto rndgen = Common::SingleTon<Cipher::BoostRandGenerator>::GetInstance();
#elif defined
        auto rndgen = Common::SingleTon<Cipher::OsslHwRandGenerator>::GetInstance();
#endif
        std::string bytes;
        rndgen->GetRandomBytes(bytes, AUTH_TOKEN_LENGTH);
        std::cout << bytes << std::endl;
        ASSERT_EQ(bytes.length(), AUTH_TOKEN_LENGTH);
        
        std::vector<uint8_t> vec;
        rndgen->GetRandomBytes(vec, AUTH_TOKEN_LENGTH);
        bytes = Common::Converter::ToHexStr(vec);
        std::cout << bytes << std::endl;
        ASSERT_EQ(bytes.length(), AUTH_TOKEN_LENGTH);
    }
    
}