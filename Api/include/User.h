/* 
 * File:   User.h
 * Author: rezaul
 *
 * Created on November 28, 2016, 2:21 PM
 */

#ifndef USER_H
#define USER_H

#include <string>
#include "Json.h"
#include "BaseOutput.h"

namespace Api {
using namespace Json;

class User : public ApiOutput<User> 
{
public:
    User();
    virtual ~User();
    
    const std::string& GetEmail() const;
    const std::string& GetName() const;
    const std::string& GetRoles() const;

    void SetEmail(std::string email);
    void SetName(std::string name);
    void SetRoles(std::string roles);
    
    REGISTER_ALL_GETTER_START
    BASE_GETTER(ApiOutput<User>)
    OWN_GETTER_START
    GETTER(User, const std::string&, "email" , &User::GetEmail),
    GETTER(User, const std::string&, "name" , &User::GetName),
    GETTER(User, const std::string&, "roles" , &User::GetRoles)
    OWN_GETTER_END
    REGISTER_ALL_GETTER_END

    REGISTER_ALL_SETTER_START
    BASE_SETTER(ApiOutput<User>)
    OWN_SETTER_START
    SETTER(User, std::string, "email", &User::SetEmail),
    SETTER(User, std::string, "name", &User::SetName),
    SETTER(User, std::string, "roles", &User::SetRoles)
    OWN_SETTER_END
    REGISTER_ALL_SETTER_END   

private:
    std::string m_name;
    std::string m_email;
    std::string m_roles;
};

} /* namespace Api */
#endif /* USER_H */

