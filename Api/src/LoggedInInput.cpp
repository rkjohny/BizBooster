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


#include "LoggedInInput.h"
#include "ServiceFacade.h"

namespace Api {

void LoggedInInput::CopyFrom(LoggedInInput&& orig)
{
    m_userId = std::move(orig.m_userId);
    m_sessionExpires = std::move(orig.m_sessionExpires);
    m_sessionToken = std::move(orig.m_sessionToken);
}

void LoggedInInput::CopyFrom(const LoggedInInput &orig)
{
    m_userId = orig.m_userId;
    m_sessionExpires = orig.m_sessionExpires;
    m_sessionToken = orig.m_sessionToken;
}

uint64_t LoggedInInput::GetSessionExpires() const
{
    return m_sessionExpires;
}

void LoggedInInput::SetSessionExpires(uint64_t expires)
{
    m_sessionExpires = expires;
}

const std::string& LoggedInInput::GetSessionToken() const
{
    return m_sessionToken;
}

void LoggedInInput::SetSessionToken(const std::string &sessionToken)
{
    m_sessionToken = sessionToken;
}

uint64_t LoggedInInput::GetUserId() const
{
    return m_userId;
}

void LoggedInInput::SetUserId(uint64_t userId)
{
    m_userId = userId;
}

std::string LoggedInInput::Name() const
{
    return "LoggedInInput";
}

std::string LoggedInInput::ToString() const
{
    return "LoggedInInput";
}

std::shared_ptr<BaseOutput> LoggedInInput::Process(Dal::Requester* requester)
{
    return ServiceFacade::UserLoggedIn(requester, this);
}


}
