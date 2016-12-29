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

#include "AuthenticatedRequester.h"

namespace Dal {

void AuthenticatedRequester::SetUser(const std::shared_ptr<User> user)
{
    m_user = std::make_signed<User>();
    m_user->copyFrom(*user);
}

const Wt::Dbo::ptr<User> AuthenticatedRequester::GetUser()
{
    return m_user;
}

bool AuthenticatedRequester::HasRole(const std::string &role)
{
    m_user->HasRole(role);
}

bool AuthenticatedRequester::HasRole(const Role &role)
{
    m_user->HasRole(role);
}


}