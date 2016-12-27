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
#include "StringUtility.h"




#define ROLE_CREATE_SUPER_USER_STR "ROLE_CREATE_SUPER_USER"

enum Role {
    ROLE_CREATE_SUPER_USER
};

class RoleUtils {
private:
    MAKE_STATIC(RoleUtils);

    static Role ToRole(const std::string &&role) {
        std::string newrole = Common::StringUtility::Trim(role);

        if (newrole.compare(ROLE_CREATE_SUPER_USER_STR) == 0) {
            return Role::ROLE_CREATE_SUPER_USER;
        }
        throw std::runtime_error("unknown roles");
    }

    static Role ToRole(const std::string &role) {
        return ToRole(std::move(role));
    }

public:

    static std::string ToStr(const Role &role) {
        switch (role) {
            case Role::ROLE_CREATE_SUPER_USER:
                return ROLE_CREATE_SUPER_USER_STR;
            default:
                throw std::runtime_error("unknown roles found");
        }
    }

    static std::string ToStr(const std::vector<Role> &&roles, const std::string &&delimeter = ",") {
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

    static std::string ToStr(const std::vector<Role> &roles, const std::string &delimeter = ",") {
        return ToStr(std::move(roles), std::move(delimeter));
    }

    static std::vector<Role> ToRoles(const std::string &&roles) {
        std::vector<std::string> v_rolesStr;
        Common::StringUtility::Tokenize(v_rolesStr, roles, ",");

        std::vector<Role> v_roles;
        for (auto &role : v_rolesStr) {
            v_roles.push_back(ToRole(role));
        }
        return v_roles;
    }

    static std::vector<Role> ToRoles(const std::string &roles) {
        return ToRoles(std::move(roles));
    }
};

#endif //BIZBOOSTER_ROLES_H
