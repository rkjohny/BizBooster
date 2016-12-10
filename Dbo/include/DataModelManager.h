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

#ifndef DATA_MODEL_MANAGER_H
#define DATA_MODEL_MANAGER_H

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


#endif //DATA_MODEL_MANAGER_H
