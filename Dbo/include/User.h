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


#ifndef ENTITY_USER_H
#define ENTITY_USER_H

#include <Wt/Dbo/Dbo>
#include <string>

#include "Json.h"
#include "SerializableSimpleEntity.h"
#include "DboDef.h"
#include "Roles.h"

#include <Wt/Dbo/Impl>
#include <Wt/Auth/Dbo/AuthInfo>

#include "DboTypes.h"


#if 0
namespace Wt {
namespace Dbo {

template<>
struct dbo_traits<Dal::User> : public dbo_default_traits {

    static const char *versionField()
    {
        return 0;
    }
};

}
}
#endif


namespace Dal {

//typedef Wt::Auth::Dbo::AuthInfo<Dal::User> AuthInfo;
//typedef Wt::Auth::Dbo::AuthToken<Dal::AuthInfo> AuthToken;

class User : public SerializableSimpleEntity<User> {
private:
    std::string m_name;
    std::string m_rolesStr;

    Wt::WDateTime m_dateCreated;
    Wt::WDateTime m_dateLastUpdated;

    Wt::Dbo::ptr<Dal::User> m_createdBy;
    Wt::Dbo::ptr<Dal::User> m_lastUpdatedBy;

    Wt::Dbo::weak_ptr<Dal::AuthInfo> m_authInfo;
    
public:
    SERIALIZEABLE(User);
    ~User() = default;

    bool HasRole(const std::string &) const;
    bool HasRole(const Role &) const;

    std::string GetEmail() const;
    void SetEmail(const std::string &email);
    
    std::string GetUnverifiedEmail() const;
    void SetUnverifiedEmail(const std::string &email);
    
    const std::string& GetName() const;
    void SetName(const std::string &name);
    
    std::string GetPassword() const;
    void SetPassword(const std::string &password);
    
    void SetPassword(const std::string &hash, const std::string &hashMethod, const std::string salt);
    
    void SetStatus(const Status &status) override;
    void SetStatusStr(const std::string &status) override;

    const std::vector<Role> GetRoles() const;
    const std::string& GetRolesStr() const;
    void SetRolesStr(const std::string &roles);
    void SetRoles(Role role);
    void SetRoles(std::vector<Role> roles);
    
    void SetPasswordHash(const std::string &hash, const std::string &hashMethod, const std::string &salt);
    std::string GetPassWordHash() const;
    std::string GetPasswordSalt() const;
    std::string GetPasswordHashMethod() const;

    void AddIdentity(const std::string &provider, const std::string &identity);
    void AddIdentity(const Wt::Dbo::ptr<Dal::AuthInfo::AuthIdentityType> &identity);
    
    Dal::AuthTokens GetAuthTokens() const;
    
    const Wt::Dbo::weak_ptr<Dal::AuthInfo>& GetAuthInfo() const;
    
    void SetEmailToken(const std::string &token, const Wt::WDateTime &expires, const Wt::Auth::User::EmailTokenRole &role);
    
    std::string GetEmailToken() const;
    Wt::WDateTime GetEmailTokenExpirationDate() const;
    Wt::Auth::User::EmailTokenRole GetEmailTokenRole() const;
    
    void SetDateCreated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateCreated() const;

    void SetDateLastUpdated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateLastUpdated() const;

    void SetCreatedBy(Wt::Dbo::ptr<Dal::User> &&user);
    Wt::Dbo::ptr<Dal::User> GetCreatedBy() const;

    void SetLastUpdatedBy(Wt::Dbo::ptr<Dal::User> &&user);
    Wt::Dbo::ptr<Dal::User> GetLastUpdatedBy() const;

    Wt::Auth::User::Status GetAuthInfoStatus() const;
    void SetAuthInfoStatus(const Wt::Auth::User::Status &status);
    
    REGISTER_GETTER_INCLUDING_BASE_START(SerializableSimpleEntity<User>)
    GETTER(User, const Wt::WDateTime&, COLUMN_DATE_CREATED, &User::GetDateCreated),
    GETTER(User, const Wt::WDateTime&, COLUMN_DATE_LAST_UPDATED, &User::GetDateLastUpdated),
    GETTER(User, std::string, "email", &User::GetEmail),
    GETTER(User, const std::string&, "name", &User::GetName),
    GETTER(User, const std::string&, "roles", &User::GetRolesStr)
    REGISTER_GETTER_INCLUDING_BASE_END


    REGISTER_SETTER_INCLUDING_BASE_START(SerializableSimpleEntity<User>)
    SETTER(User, Wt::WDateTime&, COLUMN_DATE_CREATED, &User::SetDateCreated),
    SETTER(User, Wt::WDateTime&, COLUMN_DATE_LAST_UPDATED, &User::SetDateLastUpdated),
    SETTER(User, const std::string&, "email", &User::SetEmail),
    SETTER(User, const std::string&, "name", &User::SetName),
    SETTER(User, const std::string&, "roles", &User::SetRolesStr)
    REGISTER_SETTER_INCLUDING_BASE_END

    template<class Action>
    void persist(Action &a)
    {
        Wt::Dbo::field(a, m_name, "name");
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

DBO_EXTERN_TEMPLATES(Dal::User);

#endif //ENTYRY_USER_H
