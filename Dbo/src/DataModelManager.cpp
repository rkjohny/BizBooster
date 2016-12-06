
#include "DataModelManager.h"
#include "DboConstant.h"

namespace Dal {


void DataModelManager::Run()
{
    for (int i = CURRENT_DM_VERSION_IN_PRODUCTION; i<dmUpgradeList.size(); ++i) {
        dmUpgradeList.at(i)->Execute();
    }
}

}