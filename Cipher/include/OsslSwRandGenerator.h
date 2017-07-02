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

#ifndef OPENSSL_SW_RNG_H
#define OPENSSL_SW_RNG_H

#include "OsslRandGenerator.h"

namespace Cipher {

class OsslSwRandGenerator : public OsslRandGenerator {
public:


protected:
    OsslSwRandGenerator();
    virtual ~OsslSwRandGenerator();
    NON_COPY_NON_MOVE_ABLE(OsslSwRandGenerator);

    static OsslSwRandGenerator* m_instance;
};

}
#endif /* OPENSSL_SW_RNG_H */

