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

#include "AppDisposer.h"
#include "LibLogfig.h"
#include "LibCommon.h"
#include "Json.h"
#include "LibCipher.h"
#include "LibCruxdb.h"

namespace BizBooster {

void AppDisposer::Dispose()
{
    Cruxdb::ReleaseLibrary();
    Cmarshal::Json::ReleaseLibrary();
    Cipher::ReleaseLibrary();
    Logfig::ReleaseLibrary();
    Common::ReleaseLibrary();
}

}