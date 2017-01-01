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

#include "AppSession.h"
#include "ApiDef.h"

namespace Api {

AppSession::AppSession()
{
    std::time(&m_tmExpiresOn);

    // 30 minutes to expire
    m_tmExpiresOn += DEFAULT_SESSION_TIME_OUT_IN_MSC;

    m_requester = std::shared_ptr<Dal::AuthenticatedRequester>(new Dal::AuthenticatedRequester());
}

AppSession::~AppSession()
{
}

bool AppSession::IsPinned() const
{
    return m_pinned;
}

void AppSession::SetPinned(volatile bool pinned)
{
    m_pinned = pinned;
}

bool AppSession::IsExpired()
{
    time_t now;
    std::time(&now);

    return now >= m_tmExpiresOn;
}

void AppSession::ResetExpiration()
{
    std::time(&m_tmExpiresOn);

    m_tmExpiresOn += DEFAULT_SESSION_TIME_OUT_IN_MSC; 
}

void AppSession::ResetExpiration(uint64_t msec)
{
    std::time(&m_tmExpiresOn);

    m_tmExpiresOn += msec;
}

std::weak_ptr<Dal::AuthenticatedRequester> AppSession::GetRequester()
{
    return m_requester;
}

void AppSession::SetUser(const Dal::User &user)
{
    m_requester->SetUser(user);
}

const Dal::User& AppSession::Getuser()
{
    return m_requester->GetUser();
}

}
