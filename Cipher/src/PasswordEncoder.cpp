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

#include <vector>
#include "PasswordEncoder.h"
#include "OsslHwRandGenerator.h"
#include "Converter.h"
#include "CipherDef.h"
#include "BoostRandGenerator.h"

namespace Cipher {


#if defined WT_HASH_FUNCTION && defined OPEN_SSL_CRYPTO_ENGINE
PasswordEncoder::PasswordEncoder() : 
        m_hasGenerator(Common::SingleTon<WtHashGenerator>::GetInstance()),
        m_randGenerator(Common::SingleTon<OsslHwRandGenerator>::GetInstance())
{
    
}
#elif defined WT_HASH_FUNCTION && defined BOOST_RANDOM_ENGINE
PasswordEncoder::PasswordEncoder() : 
        m_hasGenerator(Common::SingleTon<WtHashGenerator>::GetInstance()),
        m_randGenerator(Common::SingleTon<BoostRandGenerator>::GetInstance())
{
    
}
#elif defined WT_HASH_FUNCTION
PasswordEncoder::PasswordEncoder() :
        m_hasGenerator(Common::SingleTon<WtHashGenerator>::GetInstance()),
        m_randGenerator(nullptr)
{
    
}
#elif defined OPEN_SSL_CRYPTO_ENGINE
PasswordEncoder::PasswordEncoder() :
        m_hasGenerator(nullptr),
        m_randGenerator(Common::SingleTon<OsslHwRandGenerator>::GetInstance())
{
    
}
#endif

PasswordEncoder::~PasswordEncoder()
{
}

std::string PasswordEncoder::HashMethodName()
{
    return m_hasGenerator->Name(HashGenerator::HashMethod::BCRYPT);
}

std::string PasswordEncoder::Encode(const std::string &passwd, const std::string &salt)
{
    return m_hasGenerator->Generate(HashGenerator::HashMethod::BCRYPT, passwd, salt);
}

bool PasswordEncoder::Match(const std::string &passwd, const std::string &hash, const std::string &salt)
{
    return m_hasGenerator->Verify(HashGenerator::HashMethod::BCRYPT, passwd, hash, salt);
}

std::string PasswordEncoder::GenerateSalt()
{
    std::vector<uint8_t> vec;
    m_randGenerator->GetRandomBytes(vec, PASSWORD_SALT_LENGTH);    
    return Common::Converter::ToHexStr(vec);
}

void PasswordEncoder::Dispose()
{
    if (!m_isDisposed) {
        //do stuff
        m_isDisposed = true;
    }
}

}