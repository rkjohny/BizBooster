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

#ifndef OPEN_SSLRNG_H
#define OPEN_SSLRNG_H

#include "BaseRNG.h"

namespace LCrypto {

class OpenSSLRNG : public BaseRNG {
public:

protected:
    OpenSSLRNG() = default;
    virtual ~OpenSSLRNG() = default;
    NON_COPY_NON_MOVE_ABLE(OpenSSLRNG);
};

}


#endif /* OPEN_SSLRNG_H */

