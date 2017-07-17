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


#ifndef CRUXDB_APPSETTING_SERVICE_H
#define CRUXDB_APPSETTING_SERVICE_H


#include "BaseService.h"

namespace Cruxdb {

    class AppSettingService : public BaseService {
    private:
        static AppSettingService *m_instance;

    public:
        static AppSettingService *GetInstance();
        void AddOrUpdateAppSetting(Requester *requester, AppSetting &&setting);

    };
}

#endif //CRUXDB_APPSETTING_SERVICE_H
