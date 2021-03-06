
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

#ifndef WT_HASH_FUNCTION_H
#define WT_HASH_FUNCTION_H

#include "AppCommonDef.h"
#include "HashGenerator.h"
#include "SingleTon.h"
#include <Wt/Auth/HashFunction.h>
#include <string>

namespace Cipher {

class WtHashGenerator : public HashGenerator {
private:
    MAKE_SINGLE_TON(WtHashGenerator)
    
protected:   
    WtHashGenerator();
    virtual ~WtHashGenerator();
    
public:
    std::string Name(HashMethod method) override;
    
    bool Match(HashMethod method, const std::string &msg, const std::string &salt, const std::string &hash) override;
    std::string Generate(HashMethod method, const std::string &msg, const std::string &salt) override;

    void Dispose() override;
    
private:
    Wt::Auth::BCryptHashFunction m_bcryptHash;
    Wt::Auth::SHA1HashFunction m_sha1Hash;
    Wt::Auth::MD5HashFunction m_md5Hash;
};

}
#endif /* WT_HASH_FUNCTION_H */

