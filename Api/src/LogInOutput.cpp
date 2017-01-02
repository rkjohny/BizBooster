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
    m_user = orig.m_user;
    m_sessionExpiresMsc = std::move(orig.m_sessionExpiresMsc);
    m_sessionToken = std::move(orig.m_sessionExpiresMsc);
}

void LogInOutput::CopyFrom(const LogInOutput& orig)
{
    m_user = orig.m_user;
    m_sessionExpiresMsc = orig.m_sessionExpiresMsc;
    m_sessionToken = orig.m_sessionExpiresMsc;
}

std::string LogInOutput::Name() const
{
    return "LogInOutput";
}

std::string LogInOutput::ToString() const
{
    return "LogInOutput";
}

Wt::Dbo::ptr<Dal::User> LogInOutput::GetUser() const
{
    return m_user;
}

void LogInOutput::SetUser(Wt::Dbo::ptr<Dal::User> &user)
{
    m_user = user;
}

uint64_t LogInOutput::GetSessionExpires() const
{
    return m_sessionExpiresMsc;
}

void LogInOutput::SetSessionExpires(uint64_t sessionExpiresMsc)
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