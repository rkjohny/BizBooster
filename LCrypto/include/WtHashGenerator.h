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

#ifndef WT_HASH_FUNCTION_H
#define WT_HASH_FUNCTION_H

#include "AppDef.h"
#include "HashGenerator.h"
#include <Wt/Auth/HashFunction>
#include <string>

#define BCRYPT_ITERATION 10

namespace LCrypto {

class WtHashGenerator : public HashGenerator {
protected:
    WtHashGenerator();
    virtual ~WtHashGenerator();
    NON_COPY_NON_MOVE_ABLE(WtHashGenerator);
    
public:
    std::string Name(HashMethod method) override;
    
    bool Verify(HashMethod method, const std::string &msg, const std::string &hash, const std::string &salt) override;
    std::string Generate(HashMethod method, const std::string &msg, const std::string &salt) override;

    void Dispose() override;
    
    static WtHashGenerator *GetInstance();

private:
    Wt::Auth::BCryptHashFunction m_bcryptHash;
    Wt::Auth::SHA1HashFunction m_sha1Hash;
    
    static WtHashGenerator *m_instance;
};

}
#endif /* WT_HASH_FUNCTION_H */

