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

#include "AppDisposer.h"
#include "Fio.h"
#include "Common.h"
#include "Json.h"
#include "LCrypto.h"

namespace WebApp {

void AppDisposer::Dispose()
{
    Json::LoadLibrary();
    LCrypto::LoadLibrary();
    Fio::ReleaseLibrary();
    Common::ReleaseLibrary();
}

}