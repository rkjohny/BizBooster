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
#include <Wt/WTheme>

#include "User.h"
#include "PassWordEncoder.h"
#include "Roles.h"

DBO_INSTANTIATE_TEMPLATES(Dal::User);

namespace Dal {

void User::CopyFrom(const User &user)
{
    m_id = user.m_id;
    m_version = user.m_version;
    m_dateCreated = user.m_dateCreated;
    m_dateLastUpdated = user.m_dateLastUpdated;
    m_name = user.m_name;
    m_rolesStr = user.m_rolesStr;
    m_status = user.m_status;

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
    m_status = user.m_status;

    this->SetStatus(user.GetStatus());
    this->SetEmail(user.GetEmail());
    this->SetPasswordHash(user.GetPassWordHash(), user.GetPasswordHashMethod(),
            user.GetPasswordSalt());
}

void User::SetStatus(const Status &status)
{
    m_status = status;
    m_statusStr = StatusUtils::ToStr(status);

    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        switch (m_status) {
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
    m_status = StatusUtils::ToStatus(status);
    m_statusStr = status;

    auto authInfo = m_authInfo.lock();

    if (authInfo) {
        switch (m_status) {
        case Status::V:
            authInfo.modify()->setStatus(Wt::Auth::User::Status::Normal);
            break;

        default:
            authInfo.modify()->setStatus(Wt::Auth::User::Status::Disabled);
            break;
        }
    }
}

const std::string& User::GetEmail() const
{
//    std::string email = "";    
//
//    if (m_authInfo) {
//        email = m_authInfo->email();
//    }
//    return email;
    
    return m_authInfo->email();
}

const std::string &User::GetName() const
{
    return m_name;
}

void User::AddIdentity(const std::string &provider, const std::string &identity)
{
    auto authInfo = m_authInfo.lock();
    
    if (authInfo) {
        Wt::Dbo::ptr<Dal::AuthInfo::AuthIdentityType> idenPtr =
                Wt::Dbo::ptr<Dal::AuthInfo::AuthIdentityType>(new Dal::AuthInfo::AuthIdentityType(provider, identity));
        authInfo.modify()->authIdentities().insert(idenPtr);
    }
}

void User::AddIdentity(const Wt::Dbo::ptr<Dal::AuthInfo::AuthIdentityType> &identity)
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

const std::string& User::GetUnverifiedEmail() const
{
//    if (m_authInfo) {
//        return m_authInfo->unverifiedEmail();
//    }
//    return "";
    
    return m_authInfo->unverifiedEmail();
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

const std::string& User::GetPassword() const
{
//    std::string passwd = "";
//
//    if (m_authInfo) {
//        passwd = m_authInfo->passwordHash();
//    }
//    return passwd;
    
    return m_authInfo->passwordHash();
}

void User::SetPassword(const std::string &password)
{
    auto authInfo = m_authInfo.lock();
    
    if (authInfo) {
        //TODO: generate salt
        auto passwdEncoder = LCrypto::PassWordEncoder::GetInstance();
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

const std::string& User::GetPassWordHash() const
{
//    std::string hash = "";
//
//    if (m_authInfo) {
//        hash = m_authInfo->passwordHash();
//    }
//    return hash;
    
    return m_authInfo->passwordHash();
}

const std::string& User::GetPasswordSalt() const
{
//    std::string salt = "";
//
//    if (m_authInfo) {
//        salt = m_authInfo->passwordSalt();
//    }
//    return salt;
    
    return m_authInfo->passwordSalt();
}

const std::string& User::GetPasswordHashMethod() const
{
//    std::string method = "";
//
//    if (m_authInfo) {
//        method = m_authInfo->passwordMethod();
//    }
//    return method;
    
    return m_authInfo->passwordMethod();
}

bool User::HasRole(const std::string &role)
{
    return (m_rolesStr.find(std::move(role)) != std::string::npos);
}

bool User::HasRole(const Role &role)
{
    for (auto &mrole : m_roles) {
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

const std::vector<Role> &User::GetRoles() const
{
    return m_roles;
}

const std::string& User::GetRolesStr() const
{
    return m_rolesStr;
}

void User::SetRolesStr(const std::string &roles)
{
    m_rolesStr = roles;
    m_roles = RoleUtils::ToRoles(roles);
}

void User::SetRoles(Role role)
{
    m_roles.clear();
    m_roles.push_back(role);
    m_rolesStr = RoleUtils::ToStr(role);
}

void User::SetRoles(std::vector<Role> roles)
{
    m_roles.clear();
    for (auto &role : roles) {
        m_roles.push_back(role);
    }
    m_rolesStr = RoleUtils::ToStr(roles);
}

void User::SetEmailToken(const std::string &token, const Wt::WDateTime &expires, const Wt::Auth::User::EmailTokenRole &role)
{
    auto authInfo = m_authInfo.lock();
    
    if (authInfo) {
        authInfo.modify()->setEmailToken(token, expires, role);
    }
}

const Wt::Dbo::weak_ptr<Dal::AuthInfo>& User::GetAuthInfo() const
{
    return m_authInfo;
}

const Dal::AuthTokens& User::GetAuthTokens() const
{
//    if (m_authInfo) {
//        return m_authInfo->authTokens();
//    }
//    return AuthInfo::AuthTokens();
    
    return m_authInfo->authTokens();
}

Wt::Auth::User::EmailTokenRole User::GetEmailToken() const
{
//    if (m_authInfo) {
//        m_authInfo->emailTokenRole();
//    }
//    return "";
    
    return m_authInfo->emailTokenRole();
}

const Wt::WDateTime& User::GetEmailTokenExpirationDate() const
{
//    if (m_authInfo) {
//        return m_authInfo->emailTokenExpires();
//    }
//    return Wt::WDateTime();
    
    return m_authInfo->emailTokenExpires();
}

Wt::Auth::User::EmailTokenRole User::GetEmailTokenRole() const
{
//    if (m_authInfo) {
//        return m_authInfo->emailTokenRole();
//    }
//    //TODO:: what to return when AuthInfo not exists
//    return Wt::Auth::User::EmailTokenRole::VerifyEmail;
    
    return m_authInfo->emailTokenRole();
}

Wt::Auth::User::Status User::GetAuthInfoStatus() const
{
//    if (m_authInfo) {
//        return m_authInfo->status();
//    }
//    return Wt::Auth::User::Status::Disabled;
    
    return m_authInfo->status();
}

void User::SetAuthInfoStatus(const Wt::Auth::User::Status &status)
{
    auto authInfo = m_authInfo.lock();
    
    if (authInfo) {
        authInfo.modify()->setStatus(status);
    }
}


}