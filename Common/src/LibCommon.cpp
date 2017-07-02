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


#include "LibCommon.h"

namespace Common {

static bool g_loaded = false;

void LoadLibrary()
{
    //needed just to initialize the static variables
    //this method will be called form outside the library
    if (!g_loaded) {
        g_loaded = true;
    }
}

void ReleaseLibrary()
{
    if (g_loaded) {
        g_loaded = false;
    }
}

}