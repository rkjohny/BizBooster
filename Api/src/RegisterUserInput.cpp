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

#include "RegisterUserInput.h"
#include "ServiceFacade.h"

namespace Api {

//REGISTER_CLASS_DEC(RegisterUserInput, "register_user", 0)
//REGISTER_CLASS_DEC(RegisterUserInput, "RegisterUserInput", 1)

void RegisterUserInput::CopyFrom(const RegisterUserInput &orig)
{
    m_email = orig.m_email;
    m_name = orig.m_name;
    m_password = orig.m_password;
    m_roles = orig.m_roles;
    m_version = orig.m_version;
}

void RegisterUserInput::CopyFrom(RegisterUserInput &&orig)
{
    m_email = std::move(orig.m_email);
    m_name = std::move(orig.m_name);
    m_password = std::move(orig.m_password);
    m_roles = std::move(orig.m_roles);
    m_version = std::move(orig.m_version);
}

string RegisterUserInput::Name() const
{
    return "RegisterUserInput";
}

string RegisterUserInput::ToString() const
{
    return "RegisterUserInput";
}

std::shared_ptr<BaseOutput> RegisterUserInput::Process(Dal::Requester *requester)
{
    return ServiceFacade::RegisterUser(requester, this);
}

const std::string& RegisterUserInput::GetEmail() const
{
    return m_email;
}

void RegisterUserInput::SetEmail(const std::string &email)
{
    m_email = email;
}

const std::string& RegisterUserInput::GetName() const
{
    return m_name;
}

void RegisterUserInput::SetName(const std::string &name)
{
    m_name = name;
}

const std::string& RegisterUserInput::GetRoles() const
{
    return m_roles;
}

void RegisterUserInput::SetRoles(const std::string &roles)
{
    m_roles = roles;
}

int RegisterUserInput::GetVersion() const
{
    return m_version;
}

void RegisterUserInput::SetVersion(const int &version)
{
    m_version = version;
}

const std::string& RegisterUserInput::GetPassword() const
{
    return m_password;
}

void RegisterUserInput::SetPassword(const std::string &password)
{
    m_password = password;
}

const std::string& RegisterUserInput::GetStatus() const
{
    return m_status;
}

void RegisterUserInput::SetStatus(const std::string &status)
{
    m_status = status;
}

const std::string& RegisterUserInput::GetConfirmPassword() const
{
    return m_confirmPassword;
}

void RegisterUserInput::SetConfirmPassword(const std::string& confirmPassword)
{
    m_confirmPassword = confirmPassword;
}

bool RegisterUserInput::IsUseFaceBookAuth() const
{
    return m_useFaceBookAuth;
}

void RegisterUserInput::SetUseFaceBookAuth(bool useFaceBookAuth)
{
    m_useFaceBookAuth = useFaceBookAuth;
}

bool RegisterUserInput::IsUseGoogleAuth() const
{
    return m_useGoogleAuth;
}

void RegisterUserInput::SetUseGoogleAuth(bool useGoogleAuth)
{
    m_useGoogleAuth = useGoogleAuth;
}

} /* namespace Api */

