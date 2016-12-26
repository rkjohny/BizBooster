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

#include <cpprest/details/SafeInt3.hpp>

#include "PassWordEncoder.h"


namespace LCrypto {

PassWordEncoder* PassWordEncoder::m_instance = nullptr;

PassWordEncoder::PassWordEncoder()
{
    m_hasFunction = new WtHashFunction();
}

PassWordEncoder::~PassWordEncoder()
{
    delete m_hasFunction;
}

PassWordEncoder* PassWordEncoder::GetInstance()
{
    if(!m_instance) {
        m_instance = new PassWordEncoder();
    }
    return m_instance;
}

std::string PassWordEncoder::HasHMethod()
{
    return m_hasFunction->Name(BaseHashFunction::HasMethod::BCRYPT);
}

std::string PassWordEncoder::Encode(std::string passwd, std::string salt)
{
    return m_hasFunction->Generate(BaseHashFunction::HasMethod::BCRYPT, passwd, salt);
}

bool PassWordEncoder::Match(std::string passwd, std::string hash, std::string salt)
{
    return m_hasFunction->Verify(BaseHashFunction::HasMethod::BCRYPT, passwd, hash, salt);
}

}