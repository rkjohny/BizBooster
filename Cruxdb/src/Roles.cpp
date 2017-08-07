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

#include "Roles.h"
#include "StringUtils.h"
#include <stdexcept>

namespace Cruxdb {

Role RoleUtils::ToRole(const std::string &role) noexcept(false)
{
    auto newrole = Common::StringUtils::Trim(role);

    if (newrole.compare(RoleStr::ROLE_CREATE_SUPER_USER) == 0) {
        return Role::ROLE_CREATE_SUPER_USER;
    }
    if (newrole.compare(RoleStr::ROLE_INTERNAL_ROOT_USER) == 0) {
        return Role::ROLE_INTERNAL_ROOT_USER;
    }
    if (newrole.compare(RoleStr::ROLE_PROJECT_MANAGER) == 0) {
        return Role::ROLE_PROJECT_MANAGER;
    }
    if (newrole.compare(RoleStr::ROLE_SYSTEM_ADMIN) == 0) {
        return Role::ROLE_SYSTEM_ADMIN;
    }

    throw std::runtime_error("unknown roles");
}

std::string RoleUtils::ToStr(const Role &role) noexcept(false)
{
    switch (role) {
    case Role::ROLE_CREATE_SUPER_USER:
        return RoleStr::ROLE_CREATE_SUPER_USER;

    case Role::ROLE_INTERNAL_ROOT_USER:
        return RoleStr::ROLE_INTERNAL_ROOT_USER;

    case Role::ROLE_PROJECT_MANAGER:
        return RoleStr::ROLE_PROJECT_MANAGER;

    case Role::ROLE_SYSTEM_ADMIN:
        return RoleStr::ROLE_SYSTEM_ADMIN;

    default:
        throw std::runtime_error("unknown roles found");
    }
}

std::string RoleUtils::ToStr(const std::vector<Role> &roles, const std::string &delimeter) noexcept(false)
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

std::vector<Role> RoleUtils::ToRoles(const std::string &roles) noexcept(false)
{
    std::vector<std::string> v_rolesStr;
    Common::StringUtils::Tokenize(v_rolesStr, roles, ",");

    std::vector<Role> v_roles;
    for (auto &role : v_rolesStr) {
        v_roles.push_back(ToRole(role));
    }
    return v_roles;
}


}