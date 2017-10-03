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

#ifndef OPENSSL_HW_RNG_H
#define OPENSSL_HW_RNG_H

#include <openssl/ossl_typ.h>
#include "OsslRandGenerator.h"
#include "SingleTon.h"
#include "boost/thread.hpp"

namespace Cipher {

//TODO: it is test code (very early state) and not completed, we can initialize 
//      and dispose once at application load and dispose time respectively.
class OsslHwRandGenerator : public OsslRandGenerator {
    MAKE_SINGLE_TON(OsslHwRandGenerator);
    
private:
    bool Initialize() override;    
    bool DoGetRandomBytes(uint8_t *buff, int length);

public:
    void Dispose() override;
    bool GetRandomBytes(std::vector<uint8_t> &bytes, int length) override;
    bool GetRandomBytes(std::string &bytes, int length) override;
    std::string GetRandomBytes(int length) override;

protected:
    OsslHwRandGenerator();
    virtual ~OsslHwRandGenerator();    

    // These point to the same engine. One is used for ENGINE_finish, and
    // the other is used for ENGINE_free.
    static ENGINE *cm_engFoundById;
    static ENGINE *cm_engInitialized;
    static boost::mutex cm_mutex;
};

}

#endif /* OPENSSL_HW_RNG_H */

