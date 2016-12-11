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

#include "AuditableEntity.h"
//#include "User.h"


namespace Dal {

void AuditableEntity::SetDateCreated(Wt::WDateTime &dt)
{
    m_dateCreated = dt;
}

const Wt::WDateTime &AuditableEntity::GetDateCreated() const
{
    return m_dateCreated;
}


void AuditableEntity::SetDateLastUpdated(Wt::WDateTime &dt)
{
    m_dateLastUpdated = dt;
}

const Wt::WDateTime& AuditableEntity::GetDateLastUpdated() const
{
    return m_dateLastUpdated;
}

void AuditableEntity::SetCreatedBy(Wt::Dbo::ptr<Dal::User> &user)
{
    m_createdBy = user;
}

Wt::Dbo::ptr<Dal::User> AuditableEntity::GetCreatedBy() const
{
    return m_createdBy;
}

void AuditableEntity::SetLastUpdatedBy(Wt::Dbo::ptr<Dal::User> &user)
{
    m_lastUpdatedBy = user;
}

Wt::Dbo::ptr<Dal::User> AuditableEntity::GetLastUpdatedBy() const
{
    return m_lastUpdatedBy;
}


}