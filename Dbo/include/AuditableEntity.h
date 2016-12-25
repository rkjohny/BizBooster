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

#ifndef AUDITABLE_ENTITY_H
#define AUDITABLE_ENTITY_H

#include <Wt/WDateTime>
#include "SimpleEntity.h"
#include "User.h"
#include "Json.h"

#include <Wt/Dbo/WtSqlTraits>


namespace Dal {


class AuditableEntity : public SimpleEntity {
public:
    AuditableEntity() = default;
    virtual ~AuditableEntity() = default;

    virtual void SetDateCreated(Wt::WDateTime &dt);
    virtual const Wt::WDateTime& GetDateCreated() const;

    virtual void SetDateLastUpdated(Wt::WDateTime &dt);
    virtual const Wt::WDateTime& GetDateLastUpdated() const;

    virtual void SetCreatedBy(Wt::Dbo::ptr<Dal::User> &user);
    virtual Wt::Dbo::ptr<Dal::User> GetCreatedBy() const;

    virtual void SetLastUpdatedBy(Wt::Dbo::ptr<Dal::User> &user);
    virtual Wt::Dbo::ptr<Dal::User> GetLastUpdatedBy() const;


protected:
    Wt::WDateTime m_dateCreated;
    Wt::WDateTime m_dateLastUpdated;
    Wt::Dbo::ptr<Dal::User> m_createdBy;
    Wt::Dbo::ptr<Dal::User> m_lastUpdatedBy;

    REGISTER_GETTER_INCLUDING_BASE_START(SimpleEntity)
    GETTER(AuditableEntity, const Wt::WDateTime& , COLUMN_DATE_CREATED, &AuditableEntity::GetDateCreated),
    GETTER(AuditableEntity, const Wt::WDateTime& , COLUMN_DATE_LAST_UPDATED, &AuditableEntity::GetDateLastUpdated),
    GETTER(AuditableEntity, Wt::Dbo::ptr<Dal::User>, COLUMN_CREATED_BY, &AuditableEntity::GetCreatedBy),
    GETTER(AuditableEntity, Wt::Dbo::ptr<Dal::User>, COLUMN_LAST_UPDATED_BY, &AuditableEntity::GetLastUpdatedBy)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(SimpleEntity)
    SETTER(AuditableEntity, Wt::WDateTime&, COLUMN_DATE_CREATED, &AuditableEntity::SetDateCreated),
    SETTER(AuditableEntity, Wt::WDateTime&, COLUMN_DATE_LAST_UPDATED, &AuditableEntity::SetDateLastUpdated),
    SETTER(AuditableEntity, Wt::Dbo::ptr<Dal::User>&, COLUMN_CREATED_BY, &AuditableEntity::SetCreatedBy),
    SETTER(AuditableEntity, Wt::Dbo::ptr<Dal::User>&, COLUMN_LAST_UPDATED_BY, &AuditableEntity::SetLastUpdatedBy)
    REGISTER_SETTER_INCLUDING_BASE_END
};

}

#endif //AUDITABLE_ENTITY_H