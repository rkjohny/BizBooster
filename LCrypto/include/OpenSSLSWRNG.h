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

#ifndef OPENSSL_SW_RNG_H
#define OPENSSLSWRNG_H

#include "OpenSSLRNG.h"

namespace LCrypto {

class OpenSSLSWRNG : public OpenSSLRNG {
public:
    OpenSSLSWRNG();
    virtual ~OpenSSLSWRNG();

    int Initialize() override;
    int GetRandomBytes(std::string &buff, int length) override;
    static BaseRNG* GetInstance();

protected:
    OpenSSLSWRNG();
    virtual ~OpenSSLSWRNG();
    NON_COPY_NON_MOVE_ABLE(OpenSSLSWRNG);

    static bool m_isopened;
    static OpenSSLSWRNG* m_instance;
};

}
#endif /* OPENSSL_SW_RNG_H */

