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

#include "DataModelManager.h"
#include "LibCruxdb.h"
#include "CruxdbDef.h"
#include "Converter.h"
#include "LoggerFactory.h"
#include "Requester.h"
#include "InternalRootRequester.h"

namespace Cruxdb {


DataModelManager::DataModelManager()
{
    dmUpgradeList.push_back(std::make_unique<DMUpgrade_1>());
}


void DataModelManager::Run()
{
    auto baseService = Cruxdb::GetBaseService();

    size_t nextDmVersion = 0;

    auto requester = InternalRootRequester::GetInstance();
    
    baseService->CreateTables(requester);
    
    auto transaction = baseService->BeginTransaction(requester);
    
    nextDmVersion = baseService->GetNextDmVersion(requester);

    FLOG_INFO("Running Data Model Manager... pending upgrade count: %u", dmUpgradeList.size() - nextDmVersion); 

    size_t i = nextDmVersion;
    for (; i<dmUpgradeList.size(); ++i) {
        dmUpgradeList.at(i)->Execute();
    }
    if (i != nextDmVersion) {
        Cruxdb::GetAppSettingService()->AddOrUpdateAppSetting(requester, AppSetting(NEXT_DM_VERSION_KEY, Common::Converter::ToStr(i)));
    }
    
    baseService->CommitTransaction(requester, transaction);
}

}