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

#ifndef ROLES_H
#define ROLES_H

#include <string>
#include <vector>
#include "AppCommonDef.h"


namespace Cruxdb {

enum Role {
    ROLE_CREATE_SUPER_USER,
    ROLE_INTERNAL_ROOT_USER,
    ROLE_SYSTEM_ADMIN,
    ROLE_PROJECT_MANAGER
};

struct RoleStr
{
    static constexpr char *ROLE_CREATE_SUPER_USER = "ROLE_CREATE_SUPER_USER";
    static constexpr char *ROLE_INTERNAL_ROOT_USER = "ROLE_INTERNAL_ROOT_USER"; 
    static constexpr char *ROLE_SYSTEM_ADMIN = "ROLE_SYSTEM_ADMIN";
    static constexpr char *ROLE_PROJECT_MANAGER = "ROLE_PROJECT_MANAGER";
};

class RoleUtils {
private:
    MAKE_STATIC(RoleUtils);

    static Role ToRole(const std::string &&role);
    
    static Role ToRole(const std::string &role) noexcept(false);

public:

    static std::string ToStr(const Role &role) noexcept(false);

    static std::string ToStr(const std::vector<Role> &roles, const std::string &delimeter = ",") noexcept(false);

    static std::vector<Role> ToRoles(const std::string &roles) noexcept(false);
};

}
#endif //ROLES_H
