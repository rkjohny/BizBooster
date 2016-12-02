#ifndef PG_SOL_DAO_IMP_H
#define PG_SOL_DAO_IMP_H


#include "Dao.h"

namespace Dbo {
class PGSqlDaoImp : public Dao {
    friend class Dao;

protected:
    PGSqlDaoImp();

    PGSqlDaoImp(PGSqlDaoImp &);

    /**
     * Destructor is protected so that no one from outside this class can destroy
     */
    ~PGSqlDaoImp();

    static PGSqlDaoImp *m_instance;

public:
    static PGSqlDaoImp *GetInstance();

    void RegisterUser(Connector &connector, User &loggedUser, User &newUser) override;

    User *GetUser(Connector &connector, User &loggedUser, std::string email) override;
};
}


#endif