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

std::shared_ptr<WtDaoImp> WtDaoImp::m_instance = nullptr;

WtDaoImp::WtDaoImp()
{
}

WtDaoImp::~WtDaoImp()
{
    Dispose();
}

void WtDaoImp::Dispose()
{
    //     if (!m_isDosposed) {
    //        //TODO: commit/rollback if pending, close the connection
    //         m_session.Dispose();
    //         m_isDosposed = true;
    //     }

    //Just flush the session, we are not closing connection.
    m_session.flush();
}

std::shared_ptr<WtDaoImp> WtDaoImp::GetInstance()
{
    if (WtDaoImp::m_instance == nullptr) {
        WtDaoImp::m_instance = std::shared_ptr<WtDaoImp>(new WtDaoImp());
    }
    return WtDaoImp::m_instance;
}

void WtDaoImp::CreateTables(BaseRequester *requester)
{
    try {
        LOG_INFO("Creating Tables...");
        m_session.createTables();
    } catch (std::exception &e) {
        LOG_DEBUG(std::string("error:") + e.what())
        LOG_INFO("Table already exists and will not be created.");
    }
}

Wt::Dbo::Transaction WtDaoImp::BeginTransaction(BaseRequester *requester)
{
    return Wt::Dbo::Transaction(m_session);
}

bool WtDaoImp::CommitTransaction(BaseRequester *requester, Wt::Dbo::Transaction &transaction)
{
    //TODO: what will happen if this transaction is not the most recent transaction in the session?
    //      i.e, if commit returns false;
    bool commited = transaction.commit();
    return commited;
}

void WtDaoImp::RollbackTransaction(BaseRequester *requester, Wt::Dbo::Transaction& transaction)
{
    transaction.rollback();
}

bool WtDaoImp::TableExists(BaseRequester *requester, std::string table_name)
{
    int count = m_session.query<int>("SELECT count(1) FROM PG_CLASS").where("RELNAME = ?").bind(table_name);
    return (count > 0) ? true : false;
}

int WtDaoImp::GetNextDmVersion(BaseRequester *requester)
{
    int nextDmVersion = 0;

    try {
        Wt::Dbo::ptr<Dal::AppSetting> obj =
                m_session.find<Dal::AppSetting>().where("name = ?").bind(NEXT_DM_VERSION_KEY);
        if (obj) {
            std::string value = obj->GetValue();
            nextDmVersion = Common::Converter::ToInt32(std::move(value));
        }
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        nextDmVersion = 0;
    }
    return nextDmVersion;
}

void WtDaoImp::AddOrUpdateAppSetting(BaseRequester *requester, AppSetting &&setting)
{
    Wt::Dbo::ptr<Dal::AppSetting> obj =
            m_session.find<Dal::AppSetting>().where("name = ?").bind(setting.GetName());
    if (!obj) {
        obj = m_session.add<AppSetting>(new AppSetting(setting.GetName()));
    }
    obj.modify()->SetValue(setting.GetValue());
}

Wt::Dbo::ptr<User> WtDaoImp::RegisterUser(BaseRequester *requester, User *user)
{
    return this->AddEnitity(requester, user);
}

Wt::Dbo::ptr<User> WtDaoImp::GetUser(BaseRequester *requester, std::string email)
{
    Wt::Dbo::ptr<User> user;
    //user = m_session.find<Dal::User>().where("email = ? and status = ?").bind(email).bind(Status::V);
    Wt::Dbo::ptr<Dal::AuthInfo> authInfo = m_session.find<Dal::AuthInfo>().where("email = ?").bind(email);
    if (authInfo) {
        user = authInfo->user();
    }
    return user;
}

Wt::Dbo::ptr<AuthInfo> WtDaoImp::AddAuthInfo(BaseRequester *requester, AuthInfo *authInfo)
{
    Wt::Dbo::ptr<AuthInfo> authInfoAdded;
    authInfoAdded = m_session.add<AuthInfo>(authInfo);
    return authInfoAdded;
}

Wt::Dbo::ptr<AuthInfo::AuthIdentityType> WtDaoImp::AddIdentity(BaseRequester *requester, AuthInfo::AuthIdentityType *identity)
{
    Wt::Dbo::ptr<AuthInfo::AuthIdentityType> identityAdded =
            m_session.add<AuthInfo::AuthIdentityType>(identity);
    return identityAdded;
}

}


