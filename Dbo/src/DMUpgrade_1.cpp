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

#include "DMUpgrade_1.h"
#include <memory>
#include "Dal.h"
#include "Roles.h"

namespace Dal {

void DMUpgrade_1::Execute()
{    
    //Creating super user;
    User *user = new User();
    user->SetName("admin");
    user->SetEmail("admin@bizbooster.com");
    user->SetPassword("admin");
    user->SetRoles(Role::ROLE_CREATE_SUPER_USER);
    user->SetStatus(Status::V);
    user->AddIdentity("loginname", "admin");
    
    User loggedUser = User();
    Wt::Dbo::ptr<User> userAdded = Dal::GetDao()->RegisterUser(loggedUser, user);
}

}