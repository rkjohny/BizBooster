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


#ifndef ENTYRY_USER_H
#define ENTYRY_USER_H

#include <Wt/Dbo/Dbo>
#include <string>

#include "AuditableEntity.h"
#include "Json.h"
#include "SerializableEntity.h"

namespace Dal {

class User : public SerializableEntity<User> {
private:
    std::string m_email;
    std::string m_password;
    std::string m_name;
    std::string m_roles;

public:
    const std::string& GetEmail() const;
    const std::string& GetName() const;
    const std::string& GetRoles() const;
    const std::string& GetPassword() const;

    void SetEmail(std::string email);
    void SetName(std::string name);
    void SetRoles(std::string roles);
    void SetPassword(std::string password);

    REGISTER_GETTER_INCLUDING_BASE_START(SerializableEntity<User>)
    GETTER(User, const std::string&, "email", &User::GetEmail),
    GETTER(User, const std::string&, "name", &User::GetName),
    GETTER(User, const std::string&, "roles", &User::GetRoles),
    GETTER(User, const std::string&, "password", &User::GetPassword)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(SerializableEntity<User>)
    SETTER(User, std::string, "email", &User::SetEmail),
    SETTER(User, std::string, "name", &User::SetName),
    SETTER(User, std::string, "roles", &User::SetRoles),
    SETTER(User, std::string, "password", &User::SetPassword)
    REGISTER_SETTER_INCLUDING_BASE_END

    template<class Action>
    void persist(Action &a)
    {
        Wt::Dbo::field(a, m_email, "email");
        Wt::Dbo::field(a, m_name, "name");
        Wt::Dbo::field(a, m_password, "password");
        Wt::Dbo::field(a, m_roles, "roles");
        //dbo::field(a, dateCreated,     "date_created");
        //dbo::field(a, dateLastUpdated,     "date_last_updated");
    }
};
}


#endif //ENTYRY_USER_H
