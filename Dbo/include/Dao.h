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

#ifndef ABSTRACT_DAO_H
#define ABSTRACT_DAO_H

#include <string>
#include "User.h"
#include "AppSetting.h"
#include "WtSession.h"

namespace Dal {

class WtDaoImp;

class Dao {

private:
    Dao(Dao &) = delete;

    Dao &operator=(Dao &) = delete;

protected:
    Dao() = default;

public:
    virtual ~Dao() = default;

//    template<class C>
//    typename std::enable_if<std::is_base_of<Dal::AuditableEntity, C>::value, void >::type
//    PGSqlDaoImp::OnSave(C *entity) {};
//
//    template<class C>
//    typename std::enable_if<!std::is_base_of<Dal::AuditableEntity, C>::value, void >::type
//    PGSqlDaoImp::OnSave(BaseEntity *entity) {};
//
//    template<class C>
//    typename std::enable_if<std::is_base_of<Dal::BaseEntity, C>::value, Wt::Dbo::ptr<C> >::type
//    PGSqlDaoImp::AddEnitity(C *entity) {};


    virtual Wt::Dbo::ptr<Dal::User> GetUser(const Wt::Auth::User& authUser) = 0;
    virtual Wt::Auth::AbstractUserDatabase& GetUserDB() = 0;

    virtual void CreateTables() = 0;

    virtual int GetNextDmVersion() = 0;

    virtual Wt::Dbo::Transaction BeginTransaction() = 0;

    virtual bool CommitTransaction(Wt::Dbo::Transaction&) = 0;

    virtual void RollbackTransaction(Wt::Dbo::Transaction&) = 0;

    virtual bool TableExists(std::string table_name) = 0;

    virtual void AddOrUpdateAppSetting(AppSetting &&setting) = 0;

    virtual Wt::Dbo::ptr<User> RegisterUser(User &loggedUser, User *user) = 0;

    virtual Wt::Dbo::ptr<User> GetUser(User &loggedUser, std::string email) = 0;

};
}


#endif