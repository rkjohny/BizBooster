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

#include "LibLogfig.h"
#include "LoggerFactory.h"
#include "CFReaderFactory.h"

namespace Logfig {

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
        
        Logfig::LoggerFactory::Dispose();
        Logfig::CFReaderFactory::Dispose();
        
        g_loaded = false;
    }
}

}


