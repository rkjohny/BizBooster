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
#include "BaseEntity.h"
#include "AuditableEntity.h"
#include "WtSession.h"
#include "WtPgConnection.h"
#include <string>
#include <memory>
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/backend/Postgres>

#include "User.h"


namespace Dal {

class WtDaoImp : public Dao {
private:
    NON_COPY_NON_MOVE_ABLE(WtDaoImp);

    static std::shared_ptr<WtDaoImp> m_instance;
    Dal::WtSession m_session;

protected:
    WtDaoImp();

public:
    virtual ~WtDaoImp();

    void Dispose() override;
    
    template<class C>
    typename std::enable_if<(std::is_base_of<Dal::AuditableEntity, C>::value == true ||
            std::is_base_of<Dal::User, C>::value == true), void >::type
    OnSave(BaseRequester *requester, C *entity)
    {
        std::time_t curTime = std::time(nullptr);
        //std::tm *tm_local = std::localtime(&curTime);

        Wt::WDateTime wDateTime;
        wDateTime.setTime_t(curTime);

        if(entity->GetDateCreated().isNull() || !entity->GetCreatedBy()) {
            entity->SetDateCreated(wDateTime);
            //TODO: this should be requester.getUser(),
            //entity->SetCreatedBy(Wt::Dbo::ptr<C>(entity));
        }
        entity->SetDateLastUpdated(wDateTime);
        //TODO: this should be requester.getUser(),
        //entity->SetLastUpdatedBy(Wt::Dbo::ptr<C>(entity));
    }

    template<class C>
    typename std::enable_if<std::is_base_of<Dal::AuditableEntity, C>::value == false, void >::type
    OnSave(BaseRequester *requester, BaseEntity *entity)
    {
    }

    template<class C>
    typename std::enable_if<std::is_base_of<Dal::BaseEntity, C>::value == true, Wt::Dbo::ptr<C> >::type
    AddEnitity(BaseRequester *requester, C *entity)
    {
        this->OnSave(requester, entity);
        Wt::Dbo::ptr<C> newEntity = m_session.add(entity);
        return newEntity;
    }

    static std::shared_ptr<WtDaoImp> GetInstance();

    void CreateTables(BaseRequester *requester) override;

    int GetNextDmVersion(BaseRequester *requester) override;

    void AddOrUpdateAppSetting(BaseRequester *requester, AppSetting &&setting) override;

    Wt::Dbo::Transaction BeginTransaction(BaseRequester *requester) override;

    bool TableExists(BaseRequester *requester, std::string table_name) override;

    bool CommitTransaction(BaseRequester *requester, Wt::Dbo::Transaction&) override;

    void RollbackTransaction(BaseRequester *requester, Wt::Dbo::Transaction&) override;

    Wt::Dbo::ptr<User> RegisterUser(BaseRequester *requester, User *newUser) override;

    Wt::Dbo::ptr<User> GetUser(BaseRequester *requester, std::string email) override;

    Wt::Dbo::ptr<AuthInfo> AddAuthInfo(BaseRequester *requester, AuthInfo *authInfo) override;
    
    Wt::Dbo::ptr<AuthInfo::AuthIdentityType> AddIdentity(BaseRequester *requester, AuthInfo::AuthIdentityType *identity) override;
};
}


#endif