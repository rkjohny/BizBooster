#ifndef _ENTYRY_USER_H_
#define _ENTYRY_USER_H_

#include <Wt/Dbo/Dbo>
#include <string>

#include "AuditableEntity.h"


namespace Dbo {
class User : public AuditableEntity {
public:
    std::string m_email;
    std::string m_password;
    std::string m_name;
    std::string m_roles;

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
