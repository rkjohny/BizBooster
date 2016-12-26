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


#include "ServiceDisposer.h"
#include "CFReaderFactory.h"
#include "LogFactory.h"
#include "Fio.h"
#include "Common.h"
#include "Api.h"
#include "Dal.h"
#include "LCrypto.h"


namespace Rest {

void ServiceDisposer::Dispose()
{
    Api::ReleaseLibrary();
    Dal::ReleaseLibrary();
    LCrypto::ReleaseLibrary();
    Json::ReleaseLibrary();
    Fio::ReleaseLibrary();
    Common::ReleaseLibrary();
}

}