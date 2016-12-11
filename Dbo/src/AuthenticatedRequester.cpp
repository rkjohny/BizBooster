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


AuthenticatedRequester::AuthenticatedRequester(User &&user) : m_user(std::move(user))
{
}

AuthenticatedRequester::AuthenticatedRequester(const User &user) : m_user(user)
{
}

void AuthenticatedRequester::SetUser(User &&user)
{
    m_user.copyFrom(std::move(user));
}

void AuthenticatedRequester::SetUser(const User &user)
{
    m_user.copyFrom(user);
}

const User &AuthenticatedRequester::GetUser()
{
    return m_user;
}

bool AuthenticatedRequester::HasRole(std::string &&user)
{
    return m_user.HasRole(std::move(user));
}

}