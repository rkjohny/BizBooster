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

#ifndef LIB_CRUXDB_H
#define LIB_CRUXDB_H

#include "BaseService.h"
#include "UserService.h"
#include "AppSettingService.h"
#include <memory>

namespace Cruxdb {

    void LoadLibrary();
    void ReleaseLibrary();

    BaseService * GetBaseService();
    UserService * GetUserService();
    AppSettingService *GetAppSettingService();
};


#endif //LIB_CRUXDB_H
