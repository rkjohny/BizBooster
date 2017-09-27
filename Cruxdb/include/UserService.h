/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef CRUXDB_USER_SERVICE
#define CRUXDB_USER_SERVICE


#include "BaseService.h"
#include "AppSetting.h"
#include "AbstractBaseEntity.h"
#include "AbstractAuditableEntity.h"
#include "WtSession.h"
#include "WtPgConnection.h"
#include "DateTimeUtils.h"
#include "SingleTon.h"
#include <string>
#include <memory>
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "User.h"


namespace Cruxdb {

class UserService : public BaseService {
private:
    MAKE_SINGLE_TON(UserService)
    
protected:
    UserService();
    virtual ~UserService();

public:
    Wt::Dbo::ptr<User> GetUser(std::shared_ptr<Requester> requester, const std::string &provider,
                               const std::string &identity);
    Wt::Dbo::ptr<User> GetUser(std::shared_ptr<Requester> requester, const std::string &identity);

    Wt::Dbo::ptr<AuthInfo> AddAuthInfo(std::shared_ptr<Requester> requester, Wt::Dbo::ptr<AuthInfo> &authInfo);

    Wt::Dbo::ptr<AuthIdentityType> AddIdentity(std::shared_ptr<Requester> requester,
                                               Wt::Dbo::ptr<AuthIdentityType> &identity);

    Wt::Dbo::ptr<User> GetUser(std::shared_ptr<Requester> requester, int64_t id);
    Wt::Dbo::ptr<User> GetUser(std::shared_ptr<Requester> requester, const Wt::Auth::User &authUser);
    
    Cruxdb::UserDatabase& GetUserDB();
};

}


#endif