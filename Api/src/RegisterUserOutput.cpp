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

#include "RegisterUserOutput.h"

namespace Api {

RegisterUserOutput::RegisterUserOutput()
{
}

RegisterUserOutput::~RegisterUserOutput()
{
}

const User& RegisterUserOutput::GetUser() const
{
    return m_user;
}

void RegisterUserOutput::SetUser(const User& user)
{
    m_user.SetId(user.GetId());
    m_user.SetVersion(user.GetVersion());
    m_user.SetEmail(user.GetEmail());
    m_user.SetName(user.GetName());
    m_user.SetRoles(user.GetRoles());
    m_user.SetPassword(user.GetPassword());
}


} /* namespace Api */
