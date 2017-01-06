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

#include "WtDaoImp.h"
#include "DboDef.h"
#include "Converter.h"
#include "LogFactory.h"

#include "Wt/Auth/Dbo/UserDatabase"

namespace Dal {

WtDaoImp* WtDaoImp::m_instance = nullptr;

WtDaoImp::WtDaoImp()
{
    m_session = WtSession::GetInstance();
}

WtDaoImp::~WtDaoImp()
{
    Dispose();
}

void WtDaoImp::Dispose()
{
    //     if (!m_isDosposed) {
    //        //TODO: commit/rollback if pending, close the connection
    //         m_session->Dispose();
    //         m_isDosposed = true;
    //     }

    //Just flush the session, we are not closing connection.
    m_session->flush();
}

WtDaoImp* WtDaoImp::GetInstance()
{
    if (WtDaoImp::m_instance == nullptr) {
        WtDaoImp::m_instance = new WtDaoImp();
    }
    return WtDaoImp::m_instance;
}

void WtDaoImp::CreateTables(Requester *requester)
{
    try {
        LOG_INFO("Creating Tables...");
        m_session->createTables();
    } catch (std::exception &e) {
        LOG_DEBUG(std::string("Ignoring: ") + e.what())
        LOG_INFO("Table already exists and will not be created.");
    }
}

Wt::Dbo::Transaction WtDaoImp::BeginTransaction(Requester *requester)
{
    return Wt::Dbo::Transaction(*m_session);
}

bool WtDaoImp::CommitTransaction(Requester *requester, Wt::Dbo::Transaction &transaction)
{
    //TODO: what will happen if this transaction is not the most recent transaction in the session?
    //      i.e, if commit returns false;
    bool commited = transaction.commit();
    return commited;
}

void WtDaoImp::RollbackTransaction(Requester *requester, Wt::Dbo::Transaction& transaction)
{
    transaction.rollback();
}

bool WtDaoImp::TableExists(Requester *requester, std::string table_name)
{
    auto count = m_session->query<int>("SELECT count(1) FROM PG_CLASS").where("RELNAME = ?").bind(table_name);
    return (count > 0) ? true : false;
}

int WtDaoImp::GetNextDmVersion(Requester *requester)
{
    int nextDmVersion = 0;

    try {
        auto query = m_session->find<Dal::AppSetting>().where("name = ?").bind(NEXT_DM_VERSION_KEY);
        auto appSettingsPtr = query.resultValue();
        if (appSettingsPtr) {
            auto value = appSettingsPtr->GetValue();
            nextDmVersion = Common::Converter::ToInt32(value);
        }
    } catch (std::exception &e) {
        nextDmVersion = 0;
    }
    return nextDmVersion;
}

void WtDaoImp::AddOrUpdateAppSetting(Requester *requester, AppSetting &&setting)
{
    auto query = m_session->find<Dal::AppSetting>().where("name = ?").bind(setting.GetName());
    auto objPtr = query.resultValue();
    if (!objPtr) {
        objPtr = m_session->add<Dal::AppSetting>(new AppSetting(setting.GetName()));
    }
    objPtr.modify()->SetValue(setting.GetValue());
}

Wt::Dbo::ptr<User> WtDaoImp::RegisterUser(Requester *requester, User *user)
{
    return this->AddEnitity(requester, user);
}

Wt::Dbo::ptr<User> WtDaoImp::GetUser(Requester *requester, const std::string &provider, const std::string &identity)
{
    typedef Wt::Dbo::ptr<Dal::User> PUser;
    typedef Wt::Dbo::Query<PUser> QUsers;
    typedef Wt::Dbo::collection<PUser> Users;

    PUser user;

#if 0
    QUsers q = m_session->query<PUser>("select U from \"user\" U "
            "join \"auth_info\" A on U.id = A.user_id "
            "join \"auth_identity\" I on A.id = I.auth_info_id")
            .where("I.provider= ? and I.identity = ? and U.status = ?")
            .bind(provider).bind(identity).bind("V");

    Users users = q.resultList();

    if (users.size() > 0) {
        user = *(users.begin());
    }
#endif

#if 1
    auto query = m_session->query<PUser>("select U from \"user\" U "
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

Wt::Dbo::ptr<User> WtDaoImp::GetUser(Requester *requester, const std::string &identity)
{
    return GetUser(requester, DEFAULT_LOG_IN_PROVIDER, identity);
}

Wt::Dbo::ptr<AuthInfo> WtDaoImp::AddAuthInfo(Requester *requester, AuthInfo *authInfo)
{
    //    Wt::Dbo::ptr<AuthInfo> authInfoAdded;
    //    authInfoAdded = m_session->add<AuthInfo>(authInfo);
    //    return authInfoAdded;

    return m_session->add<AuthInfo>(authInfo);
}

Wt::Dbo::ptr<AuthInfo::AuthIdentityType> WtDaoImp::AddIdentity(Requester *requester, AuthInfo::AuthIdentityType *identity)
{
    //    Wt::Dbo::ptr<AuthInfo::AuthIdentityType> identityAdded =
    //            m_session->add<AuthInfo::AuthIdentityType>(identity);
    //    return identityAdded;

    return m_session->add<AuthInfo::AuthIdentityType>(identity);
}

Wt::Dbo::ptr<User> WtDaoImp::GetUser(Requester *requester, int64_t id)
{
    //    Wt::Dbo::ptr<User> user;
    //    user = m_session->find<Dal::User>().where("id = ? and status = ?").bind(id).bind(StatusStr::V);
    //    return user;

    return m_session->find<Dal::User>().where("id = ? and status = ?").bind(id).bind(StatusStr::V);
}

Dal::UserDatabase& WtDaoImp::GetUserDB()
{
    return m_session->GetUserDB();
}

}


