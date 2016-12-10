/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef PG_SOL_DAO_IMP_H
#define PG_SOL_DAO_IMP_H


#include "Dao.h"
#include "AppSetting.h"
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

    int GetNextDmVersion() override;

    void UpdateAppSetting(AppSetting &&setting) override;

    Wt::Dbo::Transaction BeginTransaction() override;

    bool TableExists(std::string table_name) override;

    bool CommitTransaction(Wt::Dbo::Transaction&) override;

    void RollbackTransaction(Wt::Dbo::Transaction&) override;

    Wt::Dbo::ptr<User> RegisterUser(User &loggedUser, User *newUser) override;

    User *GetUser(User &loggedUser, std::string email) override;
};
}


#endif