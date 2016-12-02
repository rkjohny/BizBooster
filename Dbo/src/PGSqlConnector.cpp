#include "PGSqlConnector.h"

namespace Dbo {

PGSqlConnector::PGSqlConnector()
{
}

PGSqlConnector::PGSqlConnector(string db_name) : m_postgres(Postgres(db_name))
{
    m_session.setConnection(m_postgres);
}

PGSqlConnector::~PGSqlConnector()
{
    Close();
}

void PGSqlConnector::Close()
{
    m_session.flush();
}
}