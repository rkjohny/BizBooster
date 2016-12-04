#ifndef PGSQL_CONNECTOR_H
#define PGSQL_CONNECTOR_H

#include <string>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/backend/Postgres>

#include "Connector.h"


using namespace Wt::Dbo;
using namespace Wt::Dbo::backend;
using namespace std;

namespace Dal {
class PGSqlConnector : public Connector {
    friend class Connector;

private:
    Postgres m_postgres;
    Session m_session;

protected:
    PGSqlConnector();

    PGSqlConnector(string db_name);

public:
    ~PGSqlConnector();

    void Close() override;
};
}

#endif