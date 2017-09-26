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

#include "LibCipher.h"
#include "OsslHwRandGenerator.h"
#include "WtHashGenerator.h"
#include "CipherDef.h"
#include "BoostRandGenerator.h"

namespace Cipher {

static bool g_loaded = false;

void LoadLibrary()
{
    if (!g_loaded) {
        g_loaded = true;
    }
}

void ReleaseLibrary()
{
    if (g_loaded) {
        g_loaded = false;
#ifdef OPEN_SSL_CRYPTO_ENGINE
        Common::SingleTon<OsslHwRandGenerator>::GetInstance()->Dispose();
#elif defined BOOST_RANDOM_ENGINE
        Common::SingleTon<BoostRandGenerator>::GetInstance()->Dispose();
#endif
    }
}

HashGenerator *GetHashGenerator()
{
#ifdef WT_HASH_FUNCTION
    return Common::SingleTon<WtHashGenerator>::GetInstance();
#else
    return nullptr;
#endif
}

RndGenerator *GetRndGenerator()
{
#ifdef OPEN_SSL_CRYPTO_ENGINE
    return Common::SingleTon<OsslHwRandGenerator>::GetInstance();
#elif defined BOOST_RANDOM_ENGINE
    return Common::SingleTon<BoostRandGenerator>::GetInstance();
#else
    return nullptr;
#endif
}

PasswordEncoder *GetPasswordEncoder()
{
    return Common::SingleTon<PasswordEncoder>::GetInstance();
}

}

