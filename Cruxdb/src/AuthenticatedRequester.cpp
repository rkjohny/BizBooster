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

#include "AuthenticatedRequester.h"

namespace Cruxdb {

void AuthenticatedRequester::SetUser(Wt::Dbo::ptr<Cruxdb::User> &user)
{
    m_user = user;
}

Wt::Dbo::ptr<Cruxdb::User> AuthenticatedRequester::GetUser()
{
    return m_user;
}

bool AuthenticatedRequester::HasRole(const std::string &role)
{
    return m_user->HasRole(role);
}

bool AuthenticatedRequester::HasRole(const Role &role)
{
    return m_user->HasRole(role);
}


}