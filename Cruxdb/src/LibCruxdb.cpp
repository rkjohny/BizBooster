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


#include "LibCruxdb.h"
#include "SOFactory.h"
#include "DataModelManager.h"
#include "LoggerFactory.h"
#include "CFReaderFactory.h"
#include "LibCipher.h"

namespace Cruxdb {

    static bool g_loaded = false;

    void LoadLibrary() {
        if (!g_loaded) {
            Cmarshal::Json::LoadLibrary();

            Cipher::LoadLibrary();

            LOG_DEBUG("Registering User calss...");
            REGISTER_CLASS(User, "user");

            auto config_reader = Logfig::CFReaderFactory::CreateConfigReader(
                    DBO_CONFIG_FILE_NAME, Logfig::ConFigFileType::PROPERTY_FILE);
            config_reader->SetFile(DBO_CONFIG_FILE_NAME);

            //Initializing Cruxdb objects
            Cruxdb::GetBaseService();
            Cruxdb::GetUserService();
            Cruxdb::GetAppSettingService();

            //Run data model, data model it will create tables;
            DataModelManager().Run();

            g_loaded = true;
        }
    }

    void ReleaseLibrary() {
        if (g_loaded) {

            UNREGISTER_CLASS(User, "user");

            Logfig::CFReaderFactory::DisposeConfigReader(DBO_CONFIG_FILE_NAME);

            Cruxdb::GetUserService()->Dispose();
            Cruxdb::GetAppSettingService()->Dispose();
            Cruxdb::GetBaseService()->Dispose();

            Cipher::ReleaseLibrary();
            g_loaded = false;
        }
    }


    BaseService *GetBaseService() {
        return  Common::SingleTon<BaseService>::GetInstance();
    }

    UserService *GetUserService() {
        return Common::SingleTon<UserService>::GetInstance();
    }

    AppSettingService *GetAppSettingService() {
        return Common::SingleTon<AppSettingService>::GetInstance();
    }

}