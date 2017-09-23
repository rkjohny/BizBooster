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

#ifndef AUDITABLE_ENTITY_H
#define AUDITABLE_ENTITY_H

#include <Wt/WDateTime.h>
#include "AbstractSimpleEntity.h"
#include "User.h"
#include "Json.h"

#include <Wt/Dbo/WtSqlTraits.h>


namespace Cruxdb {


class AbstractAuditableEntity : public AbstractSimpleEntity {
public:
    AbstractAuditableEntity() = default;
    virtual ~AbstractAuditableEntity() = default;

    virtual void SetDateCreated(Wt::WDateTime &dt);
    virtual const Wt::WDateTime& GetDateCreated() const;

    virtual void SetDateLastUpdated(Wt::WDateTime &dt);
    virtual const Wt::WDateTime& GetDateLastUpdated() const;

    virtual void SetCreatedBy(Wt::Dbo::ptr<Cruxdb::User> &user);
    virtual Wt::Dbo::ptr<Cruxdb::User> GetCreatedBy() const;

    virtual void SetLastUpdatedBy(Wt::Dbo::ptr<Cruxdb::User> &user);
    virtual Wt::Dbo::ptr<Cruxdb::User> GetLastUpdatedBy() const;


protected:
    Wt::WDateTime m_dateCreated;
    Wt::WDateTime m_dateLastUpdated;
    Wt::Dbo::ptr<Cruxdb::User> m_createdBy;
    Wt::Dbo::ptr<Cruxdb::User> m_lastUpdatedBy;

    REGISTER_GETTER_INCLUDING_BASE_START(AbstractSimpleEntity)
    GETTER(AbstractAuditableEntity, const Wt::WDateTime& , COLUMN_DATE_CREATED, &AbstractAuditableEntity::GetDateCreated),
    GETTER(AbstractAuditableEntity, const Wt::WDateTime& , COLUMN_DATE_LAST_UPDATED, &AbstractAuditableEntity::GetDateLastUpdated),
    GETTER(AbstractAuditableEntity, Wt::Dbo::ptr<Cruxdb::User>, COLUMN_CREATED_BY, &AbstractAuditableEntity::GetCreatedBy),
    GETTER(AbstractAuditableEntity, Wt::Dbo::ptr<Cruxdb::User>, COLUMN_LAST_UPDATED_BY, &AbstractAuditableEntity::GetLastUpdatedBy)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(AbstractSimpleEntity)
    SETTER(AbstractAuditableEntity, Wt::WDateTime&, COLUMN_DATE_CREATED, &AbstractAuditableEntity::SetDateCreated),
    SETTER(AbstractAuditableEntity, Wt::WDateTime&, COLUMN_DATE_LAST_UPDATED, &AbstractAuditableEntity::SetDateLastUpdated),
    SETTER(AbstractAuditableEntity, Wt::Dbo::ptr<Cruxdb::User>&, COLUMN_CREATED_BY, &AbstractAuditableEntity::SetCreatedBy),
    SETTER(AbstractAuditableEntity, Wt::Dbo::ptr<Cruxdb::User>&, COLUMN_LAST_UPDATED_BY, &AbstractAuditableEntity::SetLastUpdatedBy)
    REGISTER_SETTER_INCLUDING_BASE_END
};

}

#endif //AUDITABLE_ENTITY_H