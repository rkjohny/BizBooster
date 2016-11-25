/**
 * RegisterUserInput.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "RegisterUserInput.h"


namespace Api
{

REGISTER_CLASS_DEC(Api::RegisterUserInput, register_user)
REGISTER_CLASS_DEC(RegisterUserInput, RegisterUserInput)

RegisterUserInput::RegisterUserInput()
{
}

RegisterUserInput::~RegisterUserInput()
{
}

const std::string& RegisterUserInput::GetEmail() const
{
    return m_email;
}

void RegisterUserInput::SetEmail(std::string email)
{
    m_email = std::move(email);
}

const std::string& RegisterUserInput::GetName() const
{
    return m_name;
}

void RegisterUserInput::SetName(std::string name)
{
    m_name = std::move(name);
}

const std::string& RegisterUserInput::GetRoles() const
{
    return m_roles;
}

void RegisterUserInput::SetRoles(std::string roles)
{
    m_roles = std::move(roles);
}

} /* namespace Api */

