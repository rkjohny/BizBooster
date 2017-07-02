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

#include "RegisterUserOutput.h"

namespace Mocxygen {

void RegisterUserOutput::CopyFrom(RegisterUserOutput&& orig)
{
    m_user = orig.m_user;
}

void RegisterUserOutput::CopyFrom(const RegisterUserOutput& orig)
{
    m_user = orig.m_user;
}

std::string RegisterUserOutput::Name() const
{
    return "RegisterUserOutput";
}

std::string RegisterUserOutput::ToString() const
{
    return "RegisterUserOutput";
}

Wt::Dbo::ptr<User> RegisterUserOutput::GetUser() const
{
    return m_user;
}

void RegisterUserOutput::SetUser(Wt::Dbo::ptr<User> &user) 
{
    m_user = user;
}

} /* namespace Mocxygen */
