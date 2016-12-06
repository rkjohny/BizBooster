/**
 * RegisterUserOutput.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
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
}


} /* namespace Api */
