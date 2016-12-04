#ifndef _ENTYRY_USER_H_
#define _ENTYRY_USER_H_

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

    void SetEmail(std::string email);
    void SetName(std::string name);
    void SetRoles(std::string roles);

    REGISTER_ALL_GETTER_START
    BASE_GETTER(SerializableEntity<User>)
    OWN_GETTER_START
    GETTER(User, const std::string&, "email", &User::GetEmail),
    GETTER(User, const std::string&, "name", &User::GetName),
    GETTER(User, const std::string&, "roles", &User::GetRoles)
    OWN_GETTER_END
    REGISTER_ALL_GETTER_END

    REGISTER_ALL_SETTER_START
    BASE_SETTER(SerializableEntity<User>)
    OWN_SETTER_START
    SETTER(User, std::string, "email", &User::SetEmail),
    SETTER(User, std::string, "name", &User::SetName),
    SETTER(User, std::string, "roles", &User::SetRoles)
    OWN_SETTER_END
    REGISTER_ALL_SETTER_END

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


#endif
