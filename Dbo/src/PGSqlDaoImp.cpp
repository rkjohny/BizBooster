#include "PGSqlDaoImp.h"

namespace Dal {

std::shared_ptr<PGSqlDaoImp>  PGSqlDaoImp::m_instance = nullptr;

PGSqlDaoImp::PGSqlDaoImp() //:m_postgres("host=127.0.0.1 user=postgres password=1234 port=5432 dbname=biz_booster_db")
{
    m_postgres.connect("host=127.0.0.1 user=postgres password=1234 port=5432 dbname=biz_booster_db");
    m_postgres.setProperty("show-queries", "true");
    m_session.setConnection(m_postgres);
}

PGSqlDaoImp::~PGSqlDaoImp()
{
    //TODO: commit/rollback if pending, close the connection
    m_session.flush();
}

std::shared_ptr<PGSqlDaoImp> PGSqlDaoImp::GetInstance()
{
    if (PGSqlDaoImp::m_instance == nullptr) {
        PGSqlDaoImp::m_instance = std::shared_ptr<PGSqlDaoImp>(new PGSqlDaoImp());
    }
    return PGSqlDaoImp::m_instance;
}

void PGSqlDaoImp::CreateTables()
{
    m_session.mapClass<Dal::User>("user");
    m_session.createTables();
}

Wt::Dbo::Transaction PGSqlDaoImp::BeginTransaction()
{
    return Wt::Dbo::Transaction(m_session);
}

Wt::Dbo::ptr<User> PGSqlDaoImp::RegisterUser(User &loggedUser, User *user)
{
    Wt::Dbo::ptr<User> newUser = m_session.add(user);
    return newUser;
}

User *PGSqlDaoImp::GetUser(User &loggedUser, std::string email)
{
    return nullptr;
}




}


