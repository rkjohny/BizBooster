
#include "DMUpgrade_1.h"
#include <memory>
#include "Dao.h"
#include "Dal.h"
#include "AppFactory.h"

namespace Dal {

void DMUpgrade_1::Execute()
{
    std::shared_ptr<Dao> dao = Dal::GetDao();

    LOG_DEBUG("Creating tables ...");

    dao->CreateTables();
}

}