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

#include <map>

#include "Session.h"
#include "DboDef.h"

namespace Dal {

Session::Session()
{
    std::time(&m_tmExpiresOn);

    // 30 minutes to expire
    m_tmExpiresOn += DEFAULT_SESSION_TIME_OUT;

    m_requester = std::shared_ptr<Dal::AuthenticatedRequester>(new Dal::AuthenticatedRequester());
}

Session::~Session()
{

}

bool Session::IsPinned() const
{
    return m_pinned;
}

void Session::SetPinned(volatile bool pinned)
{
    m_pinned = pinned;
}

bool Session::IsExpired()
{
    time_t now;
    std::time(&now);

    return now >= m_tmExpiresOn;
}

void Session::ResetExpiration()
{
    std::time(&m_tmExpiresOn);

    m_tmExpiresOn += DEFAULT_SESSION_TIME_OUT; 
}

void Session::ResetExpiration(uint64_t msec)
{
    std::time(&m_tmExpiresOn);

    m_tmExpiresOn += msec;
}

std::weak_ptr<Dal::AuthenticatedRequester> Session::GetRequester()
{
    return m_requester;
}

void Session::SetUser(const User &user)
{
    m_requester->SetUser(user);
}

const User& Session::Getuser()
{
    return m_requester->GetUser();
}

}
