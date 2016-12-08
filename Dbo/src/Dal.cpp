//
// Created by rezaul on 12/4/16.
//


#include <AppFactory.h>
#include "Dal.h"
#include "SOFactory.h"
#include "DboConfig.h"
#include "PGSqlDaoImp.h"
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
#ifdef PGSQL
    return PGSqlDaoImp::GetInstance();
#else
    return nullptr;
#endif
}

}