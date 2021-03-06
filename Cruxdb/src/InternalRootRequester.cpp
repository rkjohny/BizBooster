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

#include <memory>

#include "InternalRootRequester.h"

namespace Cruxdb {

InternalRootRequester::InternalRootRequester()
{
    //m_user- SetLogin("root");
    //m_user->SetRoles(Role::ROLE_INTERNAL_ROOT_USER);
}

Wt::Dbo::ptr<Cruxdb::User> InternalRootRequester::GetUser()
{
    return m_user;
}

bool InternalRootRequester::HasRole(const std::string &)
{
    return true;
}

bool InternalRootRequester::HasRole(const Role &)
{
    return true;
}

}

