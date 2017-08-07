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

#ifndef CRUXDB_ABSTRACT_BASE_SERVICE
#define CRUXDB_ABSTRACT_BASE_SERVICE

#include <string>
#include <DateTimeUtils.h>
#include "User.h"
#include "AppSetting.h"
#include "WtSession.h"
#include "Requester.h"
#include "Disposable.h"

namespace Cruxdb {

class BaseService : public Common::Disposable {
private:
    MAKE_SINGLE_TON(BaseService)
    
protected:
    Cruxdb::WtSession* m_session;
    
    BaseService();
    virtual ~BaseService();

public:
    void Dispose() override;

    virtual void CreateTables(Requester *requester);

    virtual int GetNextDmVersion(Requester *requester);

    virtual Wt::Dbo::Transaction BeginTransaction(Requester *requester);

    virtual bool CommitTransaction(Requester *requester, Wt::Dbo::Transaction&);

    virtual void RollbackTransaction(Requester *requester, Wt::Dbo::Transaction&);

    virtual bool TableExists(Requester *requester, const std::string &table_name);

    template<class C>
    typename std::enable_if<(std::is_base_of<Cruxdb::AbstractAuditableEntity, C>::value == true ||
                             std::is_base_of<Cruxdb::User, C>::value == true), void >::type
    OnSave(Requester *requester, C *entity)
    {
        auto now = Common::DateTimeUtils::Now();

        if (entity->GetDateCreated().isNull() || !entity->GetCreatedBy()) {
            entity->SetDateCreated(now);
            entity->SetCreatedBy(requester->GetUser());
        }
        entity->SetDateLastUpdated(now);
        entity->SetLastUpdatedBy(requester->GetUser());
    }

//    template<class C>
//    typename std::enable_if<std::is_base_of<Cruxdb::AbstractAuditableEntity, C>::value == false, void >::type
//    OnSave(Requester *requester, AbstractBaseEntity *entity)
//    {
//    }

    template<class C>
    typename std::enable_if<std::is_base_of<Cruxdb::AbstractBaseEntity, C>::value == true, Wt::Dbo::ptr<C> >::type
    SaveEntity(Requester *requester, C *entity)
    {
        Wt::Dbo::ptr<C> newEntity;

        this->OnSave(requester, entity);

        if (entity->GetId() <= 0) {
            newEntity = m_session->add(entity);
            return newEntity;
        } else {
            newEntity = entity;
        }

        return newEntity;
    }
};
}


#endif