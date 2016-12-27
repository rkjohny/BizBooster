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

class Dao : public Common::Disposable {
private:    
    NON_COPY_NON_MOVE_ABLE(Dao);

protected:
    Dao() = default;

public:
    virtual ~Dao() = default;
   
    virtual void CreateTables() = 0;

    virtual int GetNextDmVersion() = 0;

    virtual Wt::Dbo::Transaction BeginTransaction() = 0;

    virtual bool CommitTransaction(Wt::Dbo::Transaction&) = 0;

    virtual void RollbackTransaction(Wt::Dbo::Transaction&) = 0;

    virtual bool TableExists(std::string table_name) = 0;

    virtual void AddOrUpdateAppSetting(AppSetting &&setting) = 0;

    virtual Wt::Dbo::ptr<User> RegisterUser(User &loggedUser, User *user) = 0;

    virtual Wt::Dbo::ptr<User> GetUser(User &loggedUser, std::string email) = 0;

    virtual Wt::Dbo::ptr<AuthInfo> AddAuthInfo(User &loggedUser, AuthInfo *authInfo) = 0;
    
    virtual Wt::Dbo::ptr<AuthInfo::AuthIdentityType> AddIdentity(AuthInfo::AuthIdentityType *identity) = 0;
};
}


#endif