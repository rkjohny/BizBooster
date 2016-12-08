
#include "DataModelManager.h"
#include "Dal.h"
#include "DboConfig.h"
#include "Converter.h"
#include "AppFactory.h"
#include "Converter.h"


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

    LOG_DEBUG("Running Data Model Manager... pending upgrade count: " + Common::Converter::ToStr(dmUpgradeList.size() - nextDmVersion));

    int i = nextDmVersion;
    for (; i<dmUpgradeList.size(); ++i) {
        dmUpgradeList.at(i)->Execute();
    }
    if (i != nextDmVersion) {
        dao->UpdateAppSetting(AppSetting(NEXT_DM_VERSION_KEY, Common::Converter::ToStr(i)));
    }
}

}