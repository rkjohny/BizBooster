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

#include "RndGeneratorOSSL.h"

namespace LCrypto {

class RndGeneratorOSSL_SW : public RndGeneratorOSSL {
public:


protected:
    RndGeneratorOSSL_SW();
    virtual ~RndGeneratorOSSL_SW();
    NON_COPY_NON_MOVE_ABLE(RndGeneratorOSSL_SW);

    static bool m_isopened;
    static RndGeneratorOSSL_SW* m_instance;
};

}
#endif /* OPENSSL_SW_RNG_H */

