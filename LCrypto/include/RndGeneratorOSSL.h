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

#include "RndGenerator.h"

namespace LCrypto {

class RndGeneratorOSSL : public RndGenerator {
public:

protected:
    RndGeneratorOSSL() = default;
    virtual ~RndGeneratorOSSL() = default;
    NON_COPY_NON_MOVE_ABLE(RndGeneratorOSSL);
};

}


#endif /* OPEN_SSLRNG_H */

