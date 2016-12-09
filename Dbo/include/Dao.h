#ifndef ABSTRACT_DAO_H
#define ABSTRACT_DAO_H

#include <string>
#include "User.h"
#include "AppSetting.h"


namespace Dal {

class PGSqlDaoImp;

class Dao {

private:
    Dao(Dao &) = delete;

    Dao &operator=(Dao &) = delete;

protected:
    Dao() = default;

public:
    virtual ~Dao()= default;

    virtual void CreateTables() = 0;

    virtual int GetNextDmVersion() = 0;

    virtual Wt::Dbo::Transaction BeginTransaction() = 0;

    virtual bool CommitTransaction(Wt::Dbo::Transaction&) = 0;

    virtual void RollbackTransaction(Wt::Dbo::Transaction&) = 0;

    virtual bool TableExists(std::string table_name) = 0;

    virtual void UpdateAppSetting(AppSetting &&setting) = 0;

    virtual Wt::Dbo::ptr<User> RegisterUser(User &loggedUser, User *user) = 0;

    virtual User *GetUser(User &loggedUser, std::string email) = 0;

};
}


#endif