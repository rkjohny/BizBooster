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

#ifndef OPENSSLHWRNG_H
#define OPENSSLHWRNG_H

#include <openssl/ossl_typ.h>
#include "OsslRandGenerator.h"

namespace LCrypto {

//TODO: it is test code (very early state) and not completed, we can initialize 
//      and dispose once at application load and dispose time respectively.
class OsslHwRandGenerator : public OsslRandGenerator {
private:
    bool Initialize() override;
    void Dispose() override;
    
    bool DoGetRandomBytes(uint8_t *buff, int length);

public:
    static RndGenerator* GetInstance();
    bool GetRandomBytes(std::vector<uint8_t> &bytes, int length) override;
    bool GetRandomBytes(std::string &bytes, int length) override;

protected:
    OsslHwRandGenerator();
    virtual ~OsslHwRandGenerator();
    NON_COPY_NON_MOVE_ABLE(OsslHwRandGenerator);

    // These point to the same engine. One is used for ENGINE_finish, and
    // the other is used for ENGINE_free.
    static ENGINE *engFoundById;
    static ENGINE *engInitialized;
    
    static OsslHwRandGenerator* m_instance;
};

}

#endif /* OPENSSLHWRNG_H */

