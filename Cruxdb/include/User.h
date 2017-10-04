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


#ifndef ENTITY_USER_H
#define ENTITY_USER_H

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/Types.h>
#include <string>
#include <memory>
#include "Json.h"
#include "SerializableSimpleEntity.h"
#include "CruxdbDef.h"
#include "Roles.h"

#include <Wt/Dbo/Impl.h>
#include <Wt/Auth/Dbo/AuthInfo.h>

#include "DboTypes.h"


#if 0
namespace Wt {
namespace Cruxdb {

template<>
struct dbo_traits<Cruxdb::User> : public dbo_default_traits {

    static const char *versionField()
    {
        return 0;
    }
};

}
}
#endif


namespace Cruxdb {

//typedef Wt::Auth::Cruxdb::AuthInfo<Cruxdb::User> AuthInfo;
//typedef Wt::Auth::Cruxdb::AuthToken<Cruxdb::AuthInfo> AuthToken;

class User : public SerializableSimpleEntity<User> {
public:
    SERIALIZEABLE(User);
    ~User() = default;
    
private:
    std::string m_login;
    std::string m_firstName;
    std::string m_lastName;
    std::string m_rolesStr;
    std::vector<Role> m_roles;

    Wt::WDateTime m_dateCreated;
    Wt::WDateTime m_dateLastUpdated;

    Wt::Dbo::ptr<Cruxdb::User> m_createdBy;
    Wt::Dbo::ptr<Cruxdb::User> m_lastUpdatedBy;

    Wt::Dbo::weak_ptr<Cruxdb::AuthInfo> m_authInfo;
    
public:

    bool HasRole(const std::string &) const;
    bool HasRole(const Role &) const;

    const std::string &GetFirstName() const;

    void SetFirstName(const std::string &m_firstName);

    const std::string &GetLastName() const;

    void SetLastName(const std::string &m_lastName);

    std::string GetEmail() const;
    void SetEmail(const std::string &email);
    
    std::string GetUnverifiedEmail() const;
    void SetUnverifiedEmail(const std::string &email);
    
    const std::string& GetLogin() const;
    void SetLogin(const std::string &name);
    
    std::string GetPassword() const;
    void SetPassword(const std::string &password);
    
    void SetPassword(const std::string &hash, const std::string &hashMethod, const std::string salt);
    
    void SetStatus(const Status &status) override;
    void SetStatusStr(const std::string &status) override;

    const std::vector<Role> & GetRoles() const;
    const std::string& GetRolesStr() const;
    void SetRolesStr(const std::string &roles);
    void SetRoles(Role role);
    void SetRoles(std::vector<Role> &roles);
    
    void SetPasswordHash(const std::string &hash, const std::string &hashMethod, const std::string &salt);
    std::string GetPassWordHash() const;
    std::string GetPasswordSalt() const;
    std::string GetPasswordHashMethod() const;

    void AddIdentity(const std::string &provider, const std::string &identity);
    void AddIdentity(const Wt::Dbo::ptr<Cruxdb::AuthIdentityType> &identity);
    
    AuthTokens GetAuthTokens() const;
    
    Wt::Dbo::weak_ptr<AuthInfo> GetAuthInfo() const;
    
    void SetEmailToken(const std::string &token, const Wt::WDateTime &expires, const Wt::Auth::EmailTokenRole &role);
    
    std::string GetEmailToken() const;
    Wt::WDateTime GetEmailTokenExpirationDate() const;
    Wt::Auth::EmailTokenRole GetEmailTokenRole() const;
    
    void SetDateCreated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateCreated() const;

    void SetDateLastUpdated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateLastUpdated() const;

    void SetCreatedBy(Wt::Dbo::ptr<Cruxdb::User> &&user);
    Wt::Dbo::ptr<Cruxdb::User> GetCreatedBy() const;

    void SetLastUpdatedBy(Wt::Dbo::ptr<Cruxdb::User> &&user);
    Wt::Dbo::ptr<Cruxdb::User> GetLastUpdatedBy() const;

    Wt::Auth::User::Status GetAuthInfoStatus() const;
    void SetAuthInfoStatus(const Wt::Auth::User::Status &status);
    
    REGISTER_GETTER_INCLUDING_BASE_START(SerializableSimpleEntity<User>)
    GETTER(User, const Wt::WDateTime&, COLUMN_DATE_CREATED, &User::GetDateCreated),
    GETTER(User, const Wt::WDateTime&, COLUMN_DATE_LAST_UPDATED, &User::GetDateLastUpdated),
    GETTER(User, std::string, "email", &User::GetEmail),
    GETTER(User, const std::string&, "login", &User::GetLogin),
    GETTER(User, const std::string&, "roles", &User::GetRolesStr),
    GETTER(User, const std::string&, "firstName", &User::GetFirstName),
    GETTER(User, const std::string&, "lastName", &User::GetLastName)
    REGISTER_GETTER_INCLUDING_BASE_END


    REGISTER_SETTER_INCLUDING_BASE_START(SerializableSimpleEntity<User>)
    SETTER(User, Wt::WDateTime&, COLUMN_DATE_CREATED, &User::SetDateCreated),
    SETTER(User, Wt::WDateTime&, COLUMN_DATE_LAST_UPDATED, &User::SetDateLastUpdated),
    SETTER(User, const std::string&, "email", &User::SetEmail),
    SETTER(User, const std::string&, "login", &User::SetLogin),
    SETTER(User, const std::string&, "roles", &User::SetRolesStr),
    SETTER(User, const std::string&, "firstName", &User::SetFirstName),
    SETTER(User, const std::string&, "lastName", &User::SetLastName)
    REGISTER_SETTER_INCLUDING_BASE_END

    template<class Action>
    void persist(Action &a)
    {
        Wt::Dbo::field(a, m_login, "login");
        Wt::Dbo::field(a, m_firstName, "first_name");
        Wt::Dbo::field(a, m_lastName, "last_name");
        Wt::Dbo::field(a, m_rolesStr, "roles");
        Wt::Dbo::field(a, m_statusStr, COLUMN_STATUS);
        Wt::Dbo::field(a, m_dateCreated, COLUMN_DATE_CREATED);
        Wt::Dbo::field(a, m_dateLastUpdated, COLUMN_DATE_LAST_UPDATED);

        Wt::Dbo::hasOne(a, m_authInfo, "user");

        Wt::Dbo::belongsTo(a, m_createdBy, "created_by");
        Wt::Dbo::belongsTo(a, m_lastUpdatedBy, "last_updated_by");
    }
};

}

DBO_EXTERN_TEMPLATES(Cruxdb::User);

#endif //ENTYRY_USER_H
