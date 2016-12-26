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

#include "DataModelManager.h"
#include "Dal.h"
#include "DboDef.h"
#include "Converter.h"
#include "LogFactory.h"


namespace Dal {


DataModelManager::DataModelManager()
{
    dmUpgradeList.push_back(std::make_unique<DMUpgrade_1>());
}


void DataModelManager::Run()
{
    auto dao = Dal::GetDao();
    size_t nextDmVersion = 0;

    dao->CreateTables();
    
    auto transaction = dao->BeginTransaction();
    
    nextDmVersion = dao->GetNextDmVersion();

    FLOG_DEBUG("Running Data Model Manager... pending upgrade count: %u", dmUpgradeList.size() - nextDmVersion); 

    size_t i = nextDmVersion;
    for (; i<dmUpgradeList.size(); ++i) {
        dmUpgradeList.at(i)->Execute();
    }
    if (i != nextDmVersion) {
        dao->AddOrUpdateAppSetting(AppSetting(NEXT_DM_VERSION_KEY, Common::Converter::ToStr(i)));
    }
    
    dao->CommitTransaction(transaction);
}

}