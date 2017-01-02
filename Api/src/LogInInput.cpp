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

#include "LogInInput.h"
#include "ServiceFacade.h"

namespace Api {


void LogInInput::CopyFrom(LogInInput&& orig)
{
     m_password = std::move(orig.m_password);
    m_userName = std::move(orig.m_userName);
    m_rememberMe = orig.m_rememberMe;
    m_useFacebookAuth = orig.m_useFacebookAuth;
    m_useGoogleAuth = orig.m_useGoogleAuth;
}

void LogInInput::CopyFrom(const LogInInput& orig)
{
    m_password = orig.m_password;
    m_userName = orig.m_userName;
    m_rememberMe = orig.m_rememberMe;
    m_useFacebookAuth = orig.m_useFacebookAuth;
    m_useGoogleAuth = orig.m_useGoogleAuth;
}

std::string LogInInput::Name() const
{
    return "LoginInput";
}

std::string LogInInput::ToString() const
{
    return "LoginInput";
}

std::shared_ptr<BaseOutput> LogInInput::Process(Dal::Requester *requester)
{
    return ServiceFacade::LogIn(requester, this);   
}

const std::string& LogInInput::GetPassword() const
{
    return m_password;
}

void LogInInput::SetPassword(const std::string &password)
{
    m_password = password;
}

bool LogInInput::IsUseFacebookAuth() const
{
    return m_useFacebookAuth;
}

void LogInInput::SetUseFacebookAuth(bool useFacebookAuth)
{
    m_useFacebookAuth = useFacebookAuth;
}

bool LogInInput::IsUseGoogleAuth() const
{
    return m_useGoogleAuth;
}

void LogInInput::SetUseGoogleAuth(bool useGoogleAuth)
{
    m_useGoogleAuth = useGoogleAuth;
}

const std::string& LogInInput::GetUserName() const
{
    return m_userName;
}

void LogInInput::SetUserName(const std::string& userName)
{
    m_userName = userName;
}

bool LogInInput::IsRememberMe() const
{
    return m_rememberMe;
}

void LogInInput::SetRememberMe(bool rememberMe)
{
    m_rememberMe = rememberMe;
}

}
