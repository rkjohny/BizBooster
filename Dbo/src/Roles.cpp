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

#include "Roles.h"
#include "StringUtility.h"
#include <stdexcept>

namespace Dal {

Role RoleUtils::ToRole(const std::string &role)
{
    std::string newrole = Common::StringUtility::Trim(role);

    if (newrole.compare(ROLE_CREATE_SUPER_USER_STR) == 0) {
        return Role::ROLE_CREATE_SUPER_USER;
    }
    if (newrole.compare(ROLE_INTERNAL_ROOT_USER_STR) == 0) {
        return Role::ROLE_INTERNAL_ROOT_USER;
    }
    throw std::runtime_error("unknown roles");
}

std::string RoleUtils::ToStr(const Role &role)
{
    switch (role) {
    case Role::ROLE_CREATE_SUPER_USER:
        return ROLE_CREATE_SUPER_USER_STR;
        
    case Role::ROLE_INTERNAL_ROOT_USER:
        return ROLE_INTERNAL_ROOT_USER_STR;
        
    default:
        throw std::runtime_error("unknown roles found");
    }
}

std::string RoleUtils::ToStr(const std::vector<Role> &roles, const std::string &delimeter)
{
    std::string rolesStr = "";
    bool first = true;

    for (auto &role : roles) {
        if (!first) {
            rolesStr += delimeter;
        }
        rolesStr += ToStr(role);
    }
    return rolesStr;
}

std::vector<Role> RoleUtils::ToRoles(const std::string &roles)
{
    std::vector<std::string> v_rolesStr;
    Common::StringUtility::Tokenize(v_rolesStr, roles, ",");

    std::vector<Role> v_roles;
    for (auto &role : v_rolesStr) {
        v_roles.push_back(ToRole(role));
    }
    return v_roles;
}


}