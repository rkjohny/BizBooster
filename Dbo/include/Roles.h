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

#ifndef ROLES_H
#define ROLES_H

#include <string>
#include <vector>
#include "AppDef.h"


#define ROLE_CREATE_SUPER_USER_STR "ROLE_CREATE_SUPER_USER"

namespace Dal {

enum Role {
    ROLE_CREATE_SUPER_USER
};
    
class RoleUtils {
private:
    MAKE_STATIC(RoleUtils);

    static Role ToRole(const std::string &&role);
    
    static Role ToRole(const std::string &role);

public:

    static std::string ToStr(const Role &role);

    static std::string ToStr(const std::vector<Role> &&roles, const std::string &&delimeter = ",");

    static std::string ToStr(const std::vector<Role> &roles, const std::string &delimeter = ",");

    static std::vector<Role> ToRoles(const std::string &&roles);

    static std::vector<Role> ToRoles(const std::string &roles);
};

}
#endif //ROLES_H
