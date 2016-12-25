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

#include "WtHashFunction.h"

namespace LCrypto {

WtHashFunction::WtHashFunction() : m_bcryptHash(BCRYPT_ITERATION)
{
    
}

std::string WtHashFunction::Name(HasMethod method)
{
    std::string name = "";
    
    switch (method) {
    case SHA1:
        name = m_sha1Hash.name();
        break;
    case BCRYPT:
        name = m_bcryptHash.name();
        break;
    }
    return name;
}

bool WtHashFunction::Verify(HasMethod method, const std::string &msg, const std::string &hash, const std::string &salt)
{
    bool ret = false;
    
    switch (method) {
    case SHA1:
        ret = m_sha1Hash.verify(msg, salt, hash);
        break;
        
    case BCRYPT:
        ret = m_bcryptHash.verify(msg, salt, hash);
        break;
    }
    return ret;
}

std::string WtHashFunction::Generate(HasMethod method, const std::string &msg, const std::string &salt)
{
    std::string hash;
    
    switch(method) {
    case SHA1:
        hash = m_sha1Hash.compute(msg, salt);
        break;
        
    case BCRYPT:
        hash = m_bcryptHash.compute(msg, salt);
        break;
    }
    return hash;
}

}