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

#ifndef OPENSSL_RNG_H
#define OPENSSL_RNG_H


#include "RndGenerator.h"
#include "CipherDef.h"


namespace Cipher {

class OsslRandGenerator : public RndGenerator {
public:

protected:
    OsslRandGenerator() = default;
    virtual ~OsslRandGenerator() = default;
    NON_COPY_NON_MOVE_ABLE(OsslRandGenerator);
};

}


#endif /* OPENSSL_RNG_H */

