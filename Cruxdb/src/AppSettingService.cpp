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


#include "AppSettingService.h"


namespace Cruxdb {

    void AppSettingService::AddOrUpdateAppSetting(Requester *requester, AppSetting &&setting)
    {
        auto query = m_session->find<Cruxdb::AppSetting>().where("name = ?").bind(setting.GetName());
        auto objPtr = query.resultValue();
        if (!objPtr) {
            objPtr = m_session->add<Cruxdb::AppSetting>(new AppSetting(setting.GetName()));
        }
        objPtr.modify()->SetValue(setting.GetValue());
    }
}