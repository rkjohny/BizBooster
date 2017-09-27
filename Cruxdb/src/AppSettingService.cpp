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

    Wt::Dbo::ptr<Cruxdb::AppSetting> 
    AppSettingService::AddOrUpdateAppSetting(std::shared_ptr<Requester> requester, AppSetting &&setting)
    {
        Wt::Dbo::Query<Wt::Dbo::ptr<Cruxdb::AppSetting>> query = m_session->find<Cruxdb::AppSetting>().where("name = ?").bind(setting.GetName());
        Wt::Dbo::ptr<Cruxdb::AppSetting> objPtr = query.resultValue();
        if (!objPtr) {
             return m_session->addNew<Cruxdb::AppSetting>(setting.GetName(), setting.GetValue());
        }
        objPtr.modify()->SetValue(setting.GetValue());
        return objPtr;
    }
}