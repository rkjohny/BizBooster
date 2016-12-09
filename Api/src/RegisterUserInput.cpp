/**
 * RegisterUserInput.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "RegisterUserInput.h"
#include "ServiceFacade.h"

namespace Api {

//REGISTER_CLASS_DEC(RegisterUserInput, "register_user", 0)
//REGISTER_CLASS_DEC(RegisterUserInput, "RegisterUserInput", 1)

RegisterUserInput::RegisterUserInput()
{
}

RegisterUserInput::~RegisterUserInput()
{
}

string RegisterUserInput::ToString()
{
    return "RegisterUserInput";
}

web::json::value RegisterUserInput::Process()
{
    return ServiceFacade::RegisterUser(this);
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

int RegisterUserInput::GetVersion() const
{
    return m_version;
}

void RegisterUserInput::SetVersion(int version)
{
    m_version = version;
}

const std::string& RegisterUserInput::GetPassword() const
{
    return m_password;
}

void RegisterUserInput::SetPassword(std::string password)
{
    m_password = std::move(password);
}


} /* namespace Api */

