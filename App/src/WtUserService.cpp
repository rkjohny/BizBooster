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

#include "WtUserService.h"
#include "WtAuthServices.h"
#include "LibCruxdb.h"

namespace BizBooster {

    WtUserService::WtUserService() {
        m_userDatabase = std::make_shared<Cruxdb::UserDatabase>(*m_session, &WtAuthServices::GetWtAuthService());
    }

    WtUserService::~WtUserService() {

    }


    Cruxdb::UserDatabase &WtUserService::GetUserDB() {
        return *m_userDatabase;
    }

    Wt::Dbo::ptr<Cruxdb::User>
    WtUserService::GetUser(std::shared_ptr<Cruxdb::Requester> requester, const Wt::Auth::User &authUser) {
        Wt::Dbo::ptr<Cruxdb::User> user;

        Wt::Dbo::ptr<Cruxdb::AuthInfo> authInfo = GetUserDB().find(authUser);
        if (authInfo) {
            user = authInfo->user();

            if (!user) {
                Wt::Dbo::ptr<Cruxdb::User> newUser = SaveEntity(requester, Wt::Dbo::make_ptr<Cruxdb::User>());
                authInfo.modify()->setUser(newUser);
                return newUser;
            }
        }
        return user;
    }
}
