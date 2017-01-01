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
#include "Requester.h"
#include "Disposable.h"

namespace Dal {

class Dao : public Common::Disposable {
private:    
    NON_COPY_NON_MOVE_ABLE(Dao);

protected:
    Dao() = default;

public:
    virtual ~Dao() = default;
   
    virtual void CreateTables(Requester *requester) = 0;

    virtual int GetNextDmVersion(Requester *requester) = 0;

    virtual Wt::Dbo::Transaction BeginTransaction(Requester *requester) = 0;

    virtual bool CommitTransaction(Requester *requester, Wt::Dbo::Transaction&) = 0;

    virtual void RollbackTransaction(Requester *requester, Wt::Dbo::Transaction&) = 0;

    virtual bool TableExists(Requester *requester, std::string table_name) = 0;

    virtual void AddOrUpdateAppSetting(Requester *requester, AppSetting &&setting) = 0;

    virtual Wt::Dbo::ptr<User> RegisterUser(Requester *requester, User *user) = 0;

    virtual Wt::Dbo::ptr<User> GetUser(Requester *requester, std::string email) = 0;

    virtual Wt::Dbo::ptr<AuthInfo> AddAuthInfo(Requester *requester, AuthInfo *authInfo) = 0;
    
    virtual Wt::Dbo::ptr<AuthInfo::AuthIdentityType> AddIdentity(Requester *requester, AuthInfo::AuthIdentityType *identity) = 0;

    virtual Wt::Dbo::ptr<User> GetUser(Requester *requester, int64_t id) = 0;
};
}


#endif