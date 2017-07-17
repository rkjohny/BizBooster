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

#include "AbstractAuditableEntity.h"
//#include "User.h"


namespace Cruxdb {

    void AbstractAuditableEntity::SetDateCreated(Wt::WDateTime &dt) {
        m_dateCreated = dt;
    }

    const Wt::WDateTime &AbstractAuditableEntity::GetDateCreated() const {
        return m_dateCreated;
    }


    void AbstractAuditableEntity::SetDateLastUpdated(Wt::WDateTime &dt) {
        m_dateLastUpdated = dt;
    }

    const Wt::WDateTime &AbstractAuditableEntity::GetDateLastUpdated() const {
        return m_dateLastUpdated;
    }

    void AbstractAuditableEntity::SetCreatedBy(Wt::Dbo::ptr<Cruxdb::User> &user) {
        m_createdBy = user;
    }

    Wt::Dbo::ptr<Cruxdb::User> AbstractAuditableEntity::GetCreatedBy() const {
        return m_createdBy;
    }

    void AbstractAuditableEntity::SetLastUpdatedBy(Wt::Dbo::ptr<Cruxdb::User> &user) {
        m_lastUpdatedBy = user;
    }

    Wt::Dbo::ptr<Cruxdb::User> AbstractAuditableEntity::GetLastUpdatedBy() const {
        return m_lastUpdatedBy;
    }


}