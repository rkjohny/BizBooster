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

#include <vector>
#include "PassWordEncoder.h"
#include "OsslHwRandGenerator.h"
#include "Converter.h"
#include "LibCryptoDef.h"

namespace LCrypto {

PassWordEncoder* PassWordEncoder::m_instance = nullptr;

PassWordEncoder::PassWordEncoder()
{
    m_hasGenerator = WtHashGenerator::GetInstance();
    m_randGenerator = OsslHwRandGenerator::GetInstance();
}

PassWordEncoder::~PassWordEncoder()
{
}

PassWordEncoder* PassWordEncoder::GetInstance()
{
    if(!m_instance) {
        m_instance = new PassWordEncoder();
    }
    return m_instance;
}

std::string PassWordEncoder::HashMethodName()
{
    return m_hasGenerator->Name(HashGenerator::HashMethod::BCRYPT);
}

std::string PassWordEncoder::Encode(std::string passwd, std::string salt)
{
    return m_hasGenerator->Generate(HashGenerator::HashMethod::BCRYPT, passwd, salt);
}

bool PassWordEncoder::Match(std::string passwd, std::string hash, std::string salt)
{
    return m_hasGenerator->Verify(HashGenerator::HashMethod::BCRYPT, passwd, hash, salt);
}

std::string PassWordEncoder::GenerateSalt()
{
    std::vector<uint8_t> vec;
    m_randGenerator->Initialize();
    m_randGenerator->GetRandomBytes(vec, PASSWORD_SALT_LENGTH);
    m_randGenerator->Dispose();
    
    return Common::Converter::ToHexStr(vec);
}

}