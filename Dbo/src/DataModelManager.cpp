
#include "DataModelManager.h"
#include "Dal.h"
#include "DboConfig.h"
#include "Converter.h"

#include <iostream>

namespace Dal {


DataModelManager::DataModelManager()
{
    dmUpgradeList.push_back(std::make_unique<DMUpgrade_1>());
}


void DataModelManager::Run()
{
    auto dao = Dal::GetDao();
    int nextDmVersion = 0;

    //TODO: checking only one table?
    bool tableExists = dao->TableExists("t_setting");
    if (tableExists) {
        nextDmVersion = dao->GetNextDmVersion();
    }

    int i = nextDmVersion;
    std::cout << "nextDmVersion=" << nextDmVersion << std::endl;

    for (; i<dmUpgradeList.size(); ++i) {
        dmUpgradeList.at(i)->Execute();
    }
    if (i != nextDmVersion) {
        dao->UpdateAppSetting(AppSetting(NEXT_DM_VERSION_KEY, Common::Converter::ToStr(i)));
    }
}

}