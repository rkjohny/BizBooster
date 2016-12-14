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


#include <AppFactory.h>
#include "Dal.h"
#include "SOFactory.h"
#include "DboConfig.h"
#include "WtDaoImp.h"
#include "DataModelManager.h"


namespace Dal {

static bool loaded = false;

void LoadLibrary()
{
    if (!loaded) {
        Json::LoadLibrary();

        LOG_DEBUG("Registering User calss...");
        REGISTER_CLASS(User, "user");

        auto config_reader = Common::AppFactory::CreateConfigReader(
                DBO_CONFIG_FILE_NAME, Common::ConFigFileType::PROPERTY_FILE);
        config_reader->SetFile(DBO_CONFIG_FILE_NAME);

        DataModelManager().Run();
        loaded = true;
    }
}


std::shared_ptr<Dao> GetDao()
{
#ifdef WT_DBO
    return WtDaoImp::GetInstance();
#else
    return nullptr;
#endif
}

}