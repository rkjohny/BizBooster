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

#include "LogInOutput.h"
#include "User.h"
#include "LogInHelper.h"

namespace Api {

void LogInOutput::CopyFrom(LogInOutput&& orig)
{
    m_user.copyFrom(std::move(orig.m_user));
}

void LogInOutput::CopyFrom(const LogInOutput& orig)
{
    m_user.copyFrom(orig.m_user);
}

void LogInOutput::CopyFrom(const std::shared_ptr<LogInOutput>& orig)
{
    m_user.copyFrom(orig->GetUser());
}

std::string LogInOutput::Name()
{
    return "LogInOutput";
}

std::string LogInOutput::ToString()
{
    return "LogInOutput";
}

const Dal::User& LogInOutput::GetUser() const
{
    return m_user;
}

void LogInOutput::SetUser(const Dal::User &user)
{
    m_user.copyFrom(user);
}

uint64_t LogInOutput::GetSessionExpires() const
{
    return m_sessionExpiresMsc;
}

void LogInOutput::SetSessionExpires(const uint64_t &sessionExpiresMsc)
{
    m_sessionExpiresMsc = sessionExpiresMsc;
}

const std::string& LogInOutput::GetSessionToken() const
{
    return m_sessionToken;
}

void LogInOutput::SetSessionToken(const std::string &sessionToken)
{
    m_sessionToken = sessionToken;
}

}