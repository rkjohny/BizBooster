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

#include <Wt/Auth/Identity>
#include <Wt/WTheme>

#include "User.h"
#include "PassWordEncoder.h"
#include "Roles.h"

DBO_INSTANTIATE_TEMPLATES(Cruxdb::User);

namespace Cruxdb {

void User::CopyFrom(const User &user)
{
    m_id = user.m_id;
    m_version = user.m_version;
    m_dateCreated = user.m_dateCreated;
    m_dateLastUpdated = user.m_dateLastUpdated;
    m_name = user.m_name;
    m_rolesStr = user.m_rolesStr;

    this->SetStatus(user.GetStatus());
    this->SetEmail(user.GetEmail());
    this->SetPasswordHash(user.GetPassWordHash(), user.GetPasswordHashMethod(),
            user.GetPasswordSalt());
}

void User::CopyFrom(User &&user)
{
    m_id = std::move(user.m_id);
    m_version = std::move(user.m_version);
    m_dateCreated = std::move(user.m_dateCreated);
    m_dateLastUpdated = std::move(user.m_dateLastUpdated);
    m_name = std::move(user.m_name);
    m_rolesStr = std::move(user.m_rolesStr);

    this->SetStatus(user.GetStatus());
    this->SetEmail(user.GetEmail());
    this->SetPasswordHash(user.GetPassWordHash(), user.GetPasswordHashMethod(),
            user.GetPasswordSalt());
}

void User::SetStatus(const Status &status)
{
    m_statusStr = StatusUtils::ToStr(status);

    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        switch (status) {
        case Status::V:
            authInfo.modify()->setStatus(Wt::Auth::User::Status::Normal);
            break;

        default:
            authInfo.modify()->setStatus(Wt::Auth::User::Status::Disabled);
            break;
        }
    }
}

void User::SetStatusStr(const std::string &status)
{
    m_statusStr = status;

    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        switch (StatusUtils::ToStatus(m_statusStr)) {
        case Status::V:
            authInfo.modify()->setStatus(Wt::Auth::User::Status::Normal);
            break;

        default:
            authInfo.modify()->setStatus(Wt::Auth::User::Status::Disabled);
            break;
        }
    }
}

std::string User::GetEmail() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->email();
    }
    return "";
}

const std::string &User::GetName() const
{
    return m_name;
}

void User::AddIdentity(const std::string &provider, const std::string &identity)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        Wt::Dbo::ptr<Cruxdb::AuthInfo::AuthIdentityType> idenPtr =
                Wt::Dbo::ptr<Cruxdb::AuthInfo::AuthIdentityType>(new Cruxdb::AuthInfo::AuthIdentityType(provider, identity));
        authInfo.modify()->authIdentities().insert(idenPtr);
    }
}

void User::AddIdentity(const Wt::Dbo::ptr<Cruxdb::AuthInfo::AuthIdentityType> &identity)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        authInfo.modify()->authIdentities().insert(identity);
    }
}

void User::SetEmail(const std::string &email)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        authInfo.modify()->setEmail(email);
    }
}

std::string User::GetUnverifiedEmail() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->unverifiedEmail();
    }
    return "";
}

void User::SetUnverifiedEmail(const std::string &email)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        authInfo.modify()->setUnverifiedEmail(email);
    }
}

void User::SetName(const std::string &name)
{
    m_name = name;
}

std::string User::GetPassword() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->passwordHash();
    }
    return "";
}

void User::SetPassword(const std::string &password)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        auto passwdEncoder = Cipher::PassWordEncoder::GetInstance();
        auto salt = passwdEncoder->GenerateSalt();
        auto hash = passwdEncoder->Encode(password, salt);
        auto hashMethod = passwdEncoder->HashMethodName();
        authInfo.modify()->setPassword(hash, hashMethod, salt);
    }
}

void User::SetPassword(const std::string &hash, const std::string &hashMethod, const std::string salt)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        authInfo.modify()->setPassword(hash, hashMethod, salt);
    }
}

void User::SetPasswordHash(const std::string &hash, const std::string &hashMethod, const std::string &salt)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        authInfo.modify()->setPassword(hash, hashMethod, salt);
    }
}

std::string User::GetPassWordHash() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->passwordHash();
    }
    return "";
}

std::string User::GetPasswordSalt() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->passwordSalt();
    }
    return "";
}

std::string User::GetPasswordHashMethod() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->passwordMethod();
    }
    return "";
}

bool User::HasRole(const std::string &role) const
{
    return (m_rolesStr.find(std::move(role)) != std::string::npos);
}

bool User::HasRole(const Role &role) const
{
    auto roles = RoleUtils::ToRoles(m_rolesStr);
    for (auto &mrole : roles) {
        if (mrole == role) {
            return true;
        }
    }
    return false;
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

void User::SetCreatedBy(Wt::Dbo::ptr<Cruxdb::User> &&user)
{
    m_createdBy = user;
}

Wt::Dbo::ptr<Cruxdb::User> User::GetCreatedBy() const
{
    return m_createdBy;
}

void User::SetLastUpdatedBy(Wt::Dbo::ptr<Cruxdb::User> &&user)
{
    m_lastUpdatedBy = user;
}

Wt::Dbo::ptr<Cruxdb::User> User::GetLastUpdatedBy() const
{
    return m_lastUpdatedBy;
}

const std::vector<Role> User::GetRoles() const
{
    return RoleUtils::ToRoles(m_rolesStr);
}

const std::string& User::GetRolesStr() const
{
    return m_rolesStr;
}

void User::SetRolesStr(const std::string &roles)
{
    m_rolesStr = roles;
}

void User::SetRoles(Role role)
{
    m_rolesStr = RoleUtils::ToStr(role);
}

void User::SetRoles(std::vector<Role> roles)
{
    m_rolesStr = RoleUtils::ToStr(roles);
}

void User::SetEmailToken(const std::string &token, const Wt::WDateTime &expires, const Wt::Auth::User::EmailTokenRole &role)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        authInfo.modify()->setEmailToken(token, expires, role);
    }
}

const Wt::Dbo::weak_ptr<Cruxdb::AuthInfo>& User::GetAuthInfo() const
{
    return m_authInfo;
}

Cruxdb::AuthTokens User::GetAuthTokens() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->authTokens();
    }
    return AuthInfo::AuthTokens();
}

std::string User::GetEmailToken() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->emailToken();
    }
    return "";
}

Wt::WDateTime User::GetEmailTokenExpirationDate() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->emailTokenExpires();
    }
    return Wt::WDateTime();
}

Wt::Auth::User::EmailTokenRole User::GetEmailTokenRole() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->emailTokenRole();
    }
    //TODO:: what to return when AuthInfo not exists
    return Wt::Auth::User::EmailTokenRole::VerifyEmail;
}

Wt::Auth::User::Status User::GetAuthInfoStatus() const
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        return authInfo->status();
    }
    return Wt::Auth::User::Status::Disabled;
}

void User::SetAuthInfoStatus(const Wt::Auth::User::Status &status)
{
    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        authInfo.modify()->setStatus(status);
    }
}


}