
#include "DMUpgrade.h"

#include "DboConstant.h"
#include "Connector.h"
#include "Dao.h"
#include "PGSqlConnector.h"

#include <string>

namespace Dbo {

void DMUpgrade::DMUpgrade_1()
{
    //Connector *connector = new PGSqlConnector(std::string(DB_NAME));
    Connector *connector = Connector::NewInstance(std::string(DB_NAME));
    Dao *dao = Dao::GetInstance();
    connector->Close();
}

}

