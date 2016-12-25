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

#include <Wt/Auth/Identity>

#include "User.h"
#include "PassWordEncoder.h"

DBO_INSTANTIATE_TEMPLATES(Dal::User);

namespace Dal {

void User::copyFrom(const User& user)
{
    m_id = user.m_id;
    m_version = user.m_version;
    m_dateCreated = user.m_dateCreated;
    m_dateLastUpdated = user.m_dateLastUpdated;
    m_name = user.m_name;
    m_roles = user.m_roles;
    m_status = user.m_status;

    this->SetStatus(user.GetStatus());
    this->SetEmail(user.GetEmail());
    this->SetPasswordHash(user.GetPassWordHash(), user.GetPasswordHashMethod(),
            user.GetPasswordSalt());
}

void User::copyFrom(User&& user)
{
    m_id = std::move(user.m_id);
    m_version = std::move(user.m_version);
    m_dateCreated = std::move(user.m_dateCreated);
    m_dateLastUpdated = std::move(user.m_dateLastUpdated);
    m_name = std::move(user.m_name);
    m_roles = std::move(user.m_roles);
    m_status = user.m_status;

    this->SetStatus(user.GetStatus());
    this->SetEmail(user.GetEmail());
    this->SetPasswordHash(user.GetPassWordHash(), user.GetPasswordHashMethod(),
            user.GetPasswordSalt());
}

User::User()
{
}

User::User(const User &user)
{
    copyFrom(user);
}

User::User(User &&user)
{
    copyFrom(std::move(user));
}

User::~User()
{
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

void User::InitAuthInfo()
{
    if (!m_authInfo) {
        m_authInfo = Wt::Dbo::ptr<AuthInfo>(new AuthInfo());
    }
}

void User::SetStatus(Status status)
{
    InitAuthInfo();

    switch (status) {
    case Status::V:
        m_authInfo.modify()->setStatus(Wt::Auth::User::Status::Normal);
        break;

    default:
        m_authInfo.modify()->setStatus(Wt::Auth::User::Status::Disabled);
        break;
    }
    m_status = status;
}

std::string User::GetEmail() const
{
    std::string email = "";

    if (m_authInfo) {
        email = m_authInfo->email();
    }
    return email;
}

const std::string &User::GetName() const
{
    return m_name;
}

const std::string &User::GetRoles() const
{
    return m_roles;
}

void User::AddIdentity(const std::string &provider, const std::string &identity)
{
    InitAuthInfo();

    if (m_authInfo) {
        Wt::Dbo::ptr<Dal::AuthInfo::AuthIdentityType> idenPtr =
                Wt::Dbo::ptr<Dal::AuthInfo::AuthIdentityType>(new Dal::AuthInfo::AuthIdentityType(provider, identity));
        m_authInfo.modify()->authIdentities().insert(idenPtr);
    }
}

void User::SetEmail(const std::string &email)
{
    InitAuthInfo();
    
    if (m_authInfo) {
        //auto authInfo = dynamic_cast< Wt::Dbo::ptr<AuthInfo> >(m_authInfo);
        auto authInfo = m_authInfo.modify();
        authInfo->setEmail(email);
        authInfo->setUnverifiedEmail(email);
    }
}

void User::SetName(std::string name)
{
    m_name = std::move(name);
}

void User::SetRoles(std::string roles)
{
    m_roles = std::move(roles);
}

const std::string User::GetPassword() const
{
    std::string passwd = "";

    if (m_authInfo) {
        passwd = m_authInfo->passwordHash();
    }
    return passwd;
}

void User::SetPassword(std::string password)
{
    InitAuthInfo();
    
    if (m_authInfo) {
        //TODO: generate salt
        std::string salt = "salt";
        auto passwdEncoder = Common::PassWordEncoder::GetInstance();
        auto hash = passwdEncoder->Encode(password, salt);
        auto hashMethod = passwdEncoder->HasHMethod();
        m_authInfo.modify()->setPassword(hash, hashMethod, salt);
    }
}

void User::SetPasswordHash(const std::string &hash, const std::string &hashMethod, const std::string &salt)
{
    InitAuthInfo();
    
    if (m_authInfo) {
        m_authInfo.modify()->setPassword(hash, hashMethod, salt);
    }
}

std::string User::GetPassWordHash() const
{
    std::string hash = "";

    if (m_authInfo) {
        hash = m_authInfo->passwordHash();
    }
    return hash;
}

std::string User::GetPasswordSalt() const
{
    std::string salt = "";

    if (m_authInfo) {
        salt = m_authInfo->passwordSalt();
    }
    return salt;
}

std::string User::GetPasswordHashMethod() const
{
    std::string method = "";

    if (m_authInfo) {
        method = m_authInfo->passwordMethod();
    }
    return method;
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