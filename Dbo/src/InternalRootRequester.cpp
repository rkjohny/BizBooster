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

#include <memory>

#include "InternalRootRequester.h"

namespace Dal {

InternalRootRequester* InternalRootRequester::m_instance = nullptr;

InternalRootRequester::InternalRootRequester()
{
    //m_user- SetName("root");
    //m_user->SetRoles(Role::ROLE_INTERNAL_ROOT_USER);
}

InternalRootRequester* InternalRootRequester::GetInstance()
{
    if (!m_instance) {
        m_instance = new InternalRootRequester();
    }
    return m_instance;
}

Wt::Dbo::ptr<Dal::User> InternalRootRequester::GetUser()
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

