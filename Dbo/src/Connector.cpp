#include "Connector.h"
#include "PGSqlConnector.h"

#include "DboConstant.h"

namespace Dal {

Connector::Connector()
{}

Connector::Connector(const Connector &c)
{}

Connector::~Connector()
{}

Connector *Connector::NewInstance(std::string db_name)
{
#ifdef PGSQL
    return new PGSqlConnector(db_name);
#else
    return nullptr;
#endif
}

}