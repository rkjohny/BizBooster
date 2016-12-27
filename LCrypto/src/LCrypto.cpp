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

#include "LCrypto.h"
#include "RndGeneratorOSSL_HW.h"

namespace LCrypto {

static bool g_loaded = false;

void LoadLibrary()
{
    if (!g_loaded) {
        
        RndGeneratorOSSL_HW::GetInstance()->Initialize();
        g_loaded = true;
    }
}

void ReleaseLibrary()
{
    if (g_loaded) {
        g_loaded = false;
        RndGeneratorOSSL_HW::GetInstance()->Dispose();
    }
}

}


