#include "PGSqlDaoImp.h"

namespace Dbo {

PGSqlDaoImp::PGSqlDaoImp()
{}

PGSqlDaoImp::PGSqlDaoImp(PGSqlDaoImp &d)
{}

PGSqlDaoImp::~PGSqlDaoImp()
{}

PGSqlDaoImp *PGSqlDaoImp::GetInstance()
{
    if (m_instance == NULL) {
        m_instance = new PGSqlDaoImp();
    }
    return m_instance;
}

void PGSqlDaoImp::RegisterUser(Connector &connector, User &loggedUser, User &newUser)
{

}

User *PGSqlDaoImp::GetUser(Connector &connector, User &loggedUser, std::string email)
{
    return nullptr;
}


}