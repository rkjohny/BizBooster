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

#include "UserService.h"


namespace Cruxdb {

    UserService *UserService::m_instance = nullptr;

    UserService::UserService() {
    }

    UserService::~UserService() {
    }

    UserService *UserService::GetInstance() {
        if (UserService::m_instance == nullptr) {
            UserService::m_instance = new UserService();
        }
        return UserService::m_instance;
    }


    Wt::Dbo::ptr<User>
    UserService::GetUser(Requester *requester, const std::string &provider, const std::string &identity) {
        typedef Wt::Dbo::ptr<Cruxdb::User> PUser;
        typedef Wt::Dbo::Query<PUser> QUsers;
        typedef Wt::Dbo::collection<PUser> Users;

        PUser user;

#if 1
        QUsers query = m_session->query<PUser>("select U from \"user\" U "
                                                       "join \"auth_info\" A on U.id = A.user_id "
                                                       "join \"auth_identity\" I on A.id = I.auth_info_id")
                .where("I.provider= ? and I.identity = ? and U.status = ?")
                .bind(provider).bind(identity).bind("V");

        auto users = query.resultList();

        if (users.size() > 0) {
            user = *(users.begin());
        }
#endif

        return user;
    }

    Wt::Dbo::ptr<User> UserService::GetUser(Requester *requester, const std::string &identity) {
        return GetUser(requester, DEFAULT_LOG_IN_PROVIDER, identity);
    }

    Wt::Dbo::ptr<AuthInfo> UserService::AddAuthInfo(Requester *requester, AuthInfo *authInfo) {
        return m_session->add<AuthInfo>(authInfo);
    }

    Wt::Dbo::ptr<AuthInfo::AuthIdentityType>
    UserService::AddIdentity(Requester *requester, AuthInfo::AuthIdentityType *identity) {
        return m_session->add<AuthInfo::AuthIdentityType>(identity);
    }

    Wt::Dbo::ptr<User> UserService::GetUser(Requester *requester, int64_t id) {
        return m_session->find<Cruxdb::User>().where("id = ? and status = ?").bind(id).bind(StatusStr::V);
    }

    Wt::Dbo::ptr<User> UserService::GetUser(Requester *requester, const Wt::Auth::User &authUser) {
        Wt::Dbo::ptr<Cruxdb::User> user;

        Wt::Dbo::ptr<Cruxdb::AuthInfo> authInfo = GetUserDB().find(authUser);
        if (authInfo) {
            user = authInfo->user();

            if (!user) {
                user = Wt::Dbo::ptr<Cruxdb::User>(new Cruxdb::User());
                SaveEntity(requester, static_cast<Cruxdb::User*>(user.modify()));
                authInfo.modify()->setUser(user);
                return user;
            }
        }
        return user;
    }

    Cruxdb::UserDatabase &UserService::GetUserDB() {
        return m_session->GetUserDB();
    }
}


