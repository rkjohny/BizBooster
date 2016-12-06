//
// Created by rezaul on 12/4/16.
//


#include "Dal.h"
#include "SOFactory.h"
#include "DboConstant.h"
#include "PGSqlDaoImp.h"
#include "DataModelManager.h"

namespace Dal {

    static bool loaded = false;

    void LoadLibrary()
    {
        if (!loaded) {
            Json::LoadLibrary();

            REGISTER_CLASS(User, "user");

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