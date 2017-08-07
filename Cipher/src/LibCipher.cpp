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

namespace Cipher {

static bool g_loaded = false;

void LoadLibrary()
{
    if (!g_loaded) {
        //OsslHwRandGenerator::GetInstance()->Initialize();
        g_loaded = true;
    }
}

void ReleaseLibrary()
{
    if (g_loaded) {
        g_loaded = false;
        //OsslHwRandGenerator::GetInstance()->Dispose();
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
#else
    return nullptr;
#endif
}

PasswordEncoder *GetPasswordEncoder()
{
    return Common::SingleTon<PasswordEncoder>::GetInstance();
}

}

