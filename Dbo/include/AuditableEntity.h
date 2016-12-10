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
#include "BaseEntity.h"
#include "Json.h"


#include <Wt/Dbo/WtSqlTraits>


namespace Dal {
//using namespace Wt::Dal;
class AuditableEntity : public BaseEntity {
public:
    AuditableEntity() = default;
    virtual ~AuditableEntity() = default;

    void SetDateCreated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateCreated() const;

    void SetDateLastUpdated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateLastUpdated() const;


protected:
    Wt::WDateTime m_dateCreated;
    Wt::WDateTime m_dateLastUpdated;

    REGISTER_GETTER_INCLUDING_BASE_START(BaseEntity)
    GETTER(AuditableEntity, const Wt::WDateTime& , "date_created", &AuditableEntity::GetDateCreated),
    GETTER(AuditableEntity, const Wt::WDateTime& , "date_last_updated", &AuditableEntity::GetDateLastUpdated)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(BaseEntity)
    SETTER(AuditableEntity, Wt::WDateTime&, "date_created", &AuditableEntity::SetDateCreated),
    SETTER(AuditableEntity, Wt::WDateTime&, "date_last_updated", &AuditableEntity::SetDateLastUpdated)
    REGISTER_SETTER_INCLUDING_BASE_END
};

}

#endif //AUDITABLE_ENTITY_H