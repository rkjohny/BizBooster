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
#include "DboConfig.h"



namespace Dal {
class User;
}

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


namespace Dal {

class User : public SerializableSimpleEntity<User> {
private:
    std::string m_email;
    std::string m_password;
    std::string m_name;
    std::string m_roles;

    Wt::WDateTime m_dateCreated;
    Wt::WDateTime m_dateLastUpdated;

    Wt::Dbo::ptr<Dal::User> m_createdBy;
    Wt::Dbo::ptr<Dal::User> m_lastUpdatedBy;

public:
    User();
    User(const User&);
    User(User&&);
    User& operator=(const User&);
    User& operator=(const User&&);
    void copyFrom(const User&);
    void copyFrom(User&&);

    bool HasRole(std::string &&);

    const std::string& GetEmail() const;
    const std::string& GetName() const;
    const std::string& GetRoles() const;
    const std::string& GetPassword() const;

    void SetEmail(std::string email);
    void SetName(std::string name);
    void SetRoles(std::string roles);
    void SetPassword(std::string password);

    void SetDateCreated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateCreated() const;

    void SetDateLastUpdated(Wt::WDateTime &dt);
    const Wt::WDateTime& GetDateLastUpdated() const;

    void SetCreatedBy(Wt::Dbo::ptr<Dal::User> &&user);
    Wt::Dbo::ptr<Dal::User> GetCreatedBy() const;

    void SetLastUpdatedBy(Wt::Dbo::ptr<Dal::User> &&user);
    Wt::Dbo::ptr<Dal::User> GetLastUpdatedBy() const;


    REGISTER_GETTER_INCLUDING_BASE_START(SerializableSimpleEntity<User>)
    GETTER(User, const Wt::WDateTime& , COLUMN_DATE_CREATED, &User::GetDateCreated),
    GETTER(User, const Wt::WDateTime& , COLUMN_DATE_LAST_UPDATED, &User::GetDateLastUpdated),

    GETTER(User, const std::string&, "email", &User::GetEmail),
    GETTER(User, const std::string&, "name", &User::GetName),
    GETTER(User, const std::string&, "roles", &User::GetRoles),
    GETTER(User, const std::string&, "password", &User::GetPassword)
    REGISTER_GETTER_INCLUDING_BASE_END


    REGISTER_SETTER_INCLUDING_BASE_START(SerializableSimpleEntity<User>)
    SETTER(User, Wt::WDateTime&, COLUMN_DATE_CREATED, &User::SetDateCreated),
    SETTER(User, Wt::WDateTime&, COLUMN_DATE_LAST_UPDATED, &User::SetDateLastUpdated),

    SETTER(User, std::string, "email", &User::SetEmail),
    SETTER(User, std::string, "name", &User::SetName),
    SETTER(User, std::string, "roles", &User::SetRoles),
    SETTER(User, std::string, "password", &User::SetPassword)
    REGISTER_SETTER_INCLUDING_BASE_END

    template<class Action>
    void persist(Action &a)
    {
        Wt::Dbo::field(a, m_status, COLUMN_STATUS);

        Wt::Dbo::field(a, m_dateCreated, COLUMN_DATE_CREATED);
        Wt::Dbo::field(a, m_dateLastUpdated, COLUMN_DATE_LAST_UPDATED);

        //Wt::Dbo::belongsTo(a, m_createdBy, "created_by");
        //Wt::Dbo::belongsTo(a, m_lastUpdatedBy, "last_updated_by");

        Wt::Dbo::field(a, m_email, "email");
        Wt::Dbo::field(a, m_name, "name");
        Wt::Dbo::field(a, m_password, "password");
        Wt::Dbo::field(a, m_roles, "roles");
    }
};

}



#endif //ENTYRY_USER_H
