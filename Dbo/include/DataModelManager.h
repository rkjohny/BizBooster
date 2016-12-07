
#ifndef _DATA_MODEL_MANAGER_H_
#define _DATA_MODEL_MANAGER_H_

#include "DMUpgrade.h"
#include "DMUpgrade_1.h"
#include <memory>
#include  <vector>

namespace Dal {

class DataModelManager {
private:
    std::vector<std::unique_ptr<DMUpgrade>> dmUpgradeList;

public:
    DataModelManager();

    void Run();
};

}


#endif //BIZBOOSTER_DATAMODELMANAGER_H
