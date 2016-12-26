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


#include "Dal.h"
#include "SOFactory.h"
#include "DboDef.h"
#include "WtDaoImp.h"
#include "DataModelManager.h"
#include "LogFactory.h"
#include "CFReaderFactory.h"

namespace Dal {

static bool g_loaded = false;

void LoadLibrary()
{
    if (!g_loaded) {
        Json::LoadLibrary();

        LOG_DEBUG("Registering User calss...");
        REGISTER_CLASS(User, "user");

        auto config_reader = Fio::CFReaderFactory::CreateConfigReader(
                DBO_CONFIG_FILE_NAME, Fio::ConFigFileType::PROPERTY_FILE);
        config_reader->SetFile(DBO_CONFIG_FILE_NAME);

        //Initializing Dbo objects
        Dal::GetDao();
        
        //Run data model, data model it will create tables; 
        DataModelManager().Run();
        
        g_loaded = true;
    }
}

void ReleaseLibrary()
{
    if (g_loaded) {

        UNREGISTER_CLASS(User, "user");

        Fio::CFReaderFactory::DisposeConfigReader(DBO_CONFIG_FILE_NAME);
        
        Dal::GetDao()->Dispose();
        
        g_loaded = false;
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