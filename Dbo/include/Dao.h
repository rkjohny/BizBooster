#ifndef ABSTRACT_DAO_H
#define ABSTRACT_DAO_H

#include <string>
#include "User.h"


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

    virtual Wt::Dbo::Transaction BeginTransaction() = 0;

    virtual Wt::Dbo::ptr<User> RegisterUser(User &loggedUser, User *user) = 0;

    virtual User *GetUser(User &loggedUser, std::string email) = 0;

};
}


#endif