#ifndef PG_SOL_DAO_IMP_H
#define PG_SOL_DAO_IMP_H


#include "Dao.h"
#include <string>
#include <memory>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/backend/Postgres>


namespace Dal {

class PGSqlDaoImp : public Dao {
private:
    PGSqlDaoImp(PGSqlDaoImp &&) = delete;

    PGSqlDaoImp &operator=(PGSqlDaoImp &&) = delete;

    PGSqlDaoImp(PGSqlDaoImp &) = delete;

    PGSqlDaoImp &operator=(PGSqlDaoImp &) = delete;

    Wt::Dbo::backend::Postgres m_postgres;
    Wt::Dbo::Session m_session;
    std::string m_connectionString;
    static std::shared_ptr<PGSqlDaoImp> m_instance;

protected:
    PGSqlDaoImp();

public:
    virtual ~PGSqlDaoImp();

    static std::shared_ptr<PGSqlDaoImp> GetInstance();

    void CreateTables() override;

    Wt::Dbo::Transaction BeginTransaction() override;

    Wt::Dbo::ptr<User> RegisterUser(User &loggedUser, User *newUser) override;

    User *GetUser(User &loggedUser, std::string email) override;
};
}


#endif