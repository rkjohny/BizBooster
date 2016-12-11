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

#define ROLE_CREATE_SUPER_USER_STR "ROLE_CREATE_SUPER_USER"
#define ROLE_SYSTEM_USER_STR "ROLE_SYSTEM_USER"
#define ROLE_GUEST_USER_STR "ROLE_GUEST_USER"
#define ROLE_SYSTEM_ADMIN_STR "ROLE_SYSTEM_ADMIN"
#define ROLE_USER_ADMIN_STR "ROLE_USER_ADMIN"
#define ROLE_INSTANCE_ADMIN_STR "ROLE_INSTANCE_ADMIN"

enum Role
{
    ROLE_CREATE_SUPER_USER,
    ROLE_SYSTEM_USER,
    ROLE_GUEST_USER,
    ROLE_SYSTEM_ADMIN,
    ROLE_USER_ADMIN,
    ROLE_ROOT_USER,
    ROLE_INSTANCE_ADMIN
};


#endif //BIZBOOSTER_ROLES_H
