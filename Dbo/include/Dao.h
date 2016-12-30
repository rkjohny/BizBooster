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
#include "BaseRequester.h"

namespace Dal {

class Dao : public Common::Disposable {
private:    
    NON_COPY_NON_MOVE_ABLE(Dao);

protected:
    Dao() = default;

public:
    virtual ~Dao() = default;
   
    virtual void CreateTables(BaseRequester *requester) = 0;

    virtual int GetNextDmVersion(BaseRequester *requester) = 0;

    virtual Wt::Dbo::Transaction BeginTransaction(BaseRequester *requester) = 0;

    virtual bool CommitTransaction(BaseRequester *requester, Wt::Dbo::Transaction&) = 0;

    virtual void RollbackTransaction(BaseRequester *requester, Wt::Dbo::Transaction&) = 0;

    virtual bool TableExists(BaseRequester *requester, std::string table_name) = 0;

    virtual void AddOrUpdateAppSetting(BaseRequester *requester, AppSetting &&setting) = 0;

    virtual Wt::Dbo::ptr<User> RegisterUser(BaseRequester *requester, User *user) = 0;

    virtual Wt::Dbo::ptr<User> GetUser(BaseRequester *requester, std::string email) = 0;

    virtual Wt::Dbo::ptr<AuthInfo> AddAuthInfo(BaseRequester *requester, AuthInfo *authInfo) = 0;
    
    virtual Wt::Dbo::ptr<AuthInfo::AuthIdentityType> AddIdentity(BaseRequester *requester, AuthInfo::AuthIdentityType *identity) = 0;
};
}


#endif