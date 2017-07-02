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


#include "ServiceDisposer.h"
#include "CFReaderFactory.h"
#include "LoggerFactory.h"
#include "LibLogfig.h"
#include "LibCommon.h"
#include "LibMocxygen.h"
#include "LibCruxdb.h"
#include "LibCipher.h"


namespace Pantoon {

void ServiceDisposer::Dispose()
{
    Mocxygen::ReleaseLibrary();
    Cruxdb::ReleaseLibrary();
    Cipher::ReleaseLibrary();
    Cmarshal::Json::ReleaseLibrary();
    Logfig::ReleaseLibrary();
    Common::ReleaseLibrary();
}

}
