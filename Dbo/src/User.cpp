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

#include "User.h"

DBO_INSTANTIATE_TEMPLATES(Dal::User);

namespace Dal {

void User::copyFrom(const User& user)
{
    m_id = user.m_id;
    m_version = user.m_version;
    m_dateCreated = user.m_dateCreated;
    m_dateLastUpdated = user.m_dateLastUpdated;
    m_name = user.m_name;
    m_password = user.m_password;
    m_email = user.m_email;
    m_roles = user.m_roles;
    m_status = user.m_status;
}

void User::copyFrom(User&& user)
{
    m_id = std::move(user.m_id);
    m_version = std::move(user.m_version);
    m_dateCreated = std::move(user.m_dateCreated);
    m_dateLastUpdated = std::move(user.m_dateLastUpdated);
    m_name = std::move(user.m_name);
    m_password = std::move(user.m_password);
    m_email = std::move(user.m_email);
    m_roles = std::move(user.m_roles);
    m_status = user.m_status;
}

User::User()
{
    m_status = Status::V;
}

User::User(const User &user)
{
    copyFrom(user);
}

User::User(User &&user)
{
    copyFrom(std::move(user));
}

User& User::operator=(const User &user)
{
    copyFrom(user);
    return *this;
}

User& User::operator=(const User &&user)
{
    copyFrom(std::move(user));
    return *this;
}

const std::string &User::GetEmail() const
{
    return m_email;
}

const std::string &User::GetName() const
{
    return m_name;
}

const std::string &User::GetRoles() const
{
    return m_roles;
}

void User::SetEmail(std::string email)
{
    m_email = std::move(email);
}

void User::SetName(std::string name)
{
    m_name = std::move(name);
}

void User::SetRoles(std::string roles)
{
    m_roles = std::move(roles);
}

const std::string &User::GetPassword() const
{
    return m_password;
}

void User::SetPassword(std::string password)
{
    m_password = std::move(password);
}

bool User::HasRole(std::string &&role)
{
    return (m_roles.find(std::move(role)) != std::string::npos);
}


void User::SetDateCreated(Wt::WDateTime &dt)
{
    m_dateCreated = dt;
}

const Wt::WDateTime &User::GetDateCreated() const
{
    return m_dateCreated;
}

void User::SetDateLastUpdated(Wt::WDateTime &dt)
{
    m_dateLastUpdated = dt;
}

const Wt::WDateTime& User::GetDateLastUpdated() const
{
    return m_dateLastUpdated;
}

void User::SetCreatedBy(Wt::Dbo::ptr<Dal::User> &&user)
{
    m_createdBy = user;
}

Wt::Dbo::ptr<Dal::User> User::GetCreatedBy() const
{
    return m_createdBy;
}

void User::SetLastUpdatedBy(Wt::Dbo::ptr<Dal::User> &&user)
{
    m_lastUpdatedBy = user;
}

Wt::Dbo::ptr<Dal::User> User::GetLastUpdatedBy() const
{
    return m_lastUpdatedBy;
}

}