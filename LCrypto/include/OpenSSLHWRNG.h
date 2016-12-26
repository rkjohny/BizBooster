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
#include "OpenSSLRNG.h"


namespace LCrypto {

class OpenSSLHWRNG : public OpenSSLRNG {
public:

    int Initialize() override;
    int GetRandomBytes(std::vector<uint8_t> &bytes, int length) override;
    static BaseRNG* GetInstance();
    void Dispose() override;
    
protected:
    OpenSSLHWRNG();
    virtual ~OpenSSLHWRNG();
    NON_COPY_NON_MOVE_ABLE(OpenSSLHWRNG);

    static bool m_isopened;
    
    // These point to the same engine. One is used for ENGINE_finish, and
    // the other is used for ENGINE_free.
    static ENGINE *eng1;
    static ENGINE *eng2;
    
    static OpenSSLHWRNG* m_instance;
};

}

#endif /* OPENSSLHWRNG_H */

