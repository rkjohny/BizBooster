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

#include "LoginOutput.h"
#include "User.h"
#include "LoginHelper.h"

namespace Mocxygen {

void LoginOutput::CopyFrom(const LoginOutput&& orig)
{
    if (orig.m_entity) {
        m_entity = std::move(orig.m_entity);
    }
    if (orig.m_sessionExpiresSec) {
        m_sessionExpiresSec = std::move(orig.m_sessionExpiresSec);
    }
    if (orig.m_sessionToken) {
        m_sessionToken = std::move(orig.m_sessionToken);
    }
}

void LoginOutput::CopyFrom(const LoginOutput& orig)
{
    if (orig.m_entity) {
        m_entity = orig.m_entity;
    }
    if (orig.m_sessionExpiresSec) {
        m_sessionExpiresSec = *orig.m_sessionExpiresSec;
    }
    if (orig.m_sessionToken) {
        m_sessionToken = *orig.m_sessionToken;
    }
}

std::string LoginOutput::Name() const
{
    return "LogInOutput";
}

std::string LoginOutput::ToString() const
{
    return "LogInOutput";
}

const boost::optional<uint64_t> & LoginOutput::GetSessionExpiresInSec() const
{
    return m_sessionExpiresSec;
}

void LoginOutput::SetSessionExpiresInSec(const boost::optional<uint64_t> &sessionExpiresSec)
{
    m_sessionExpiresSec = sessionExpiresSec;
}

const boost::optional<std::string> & LoginOutput::GetSessionToken() const
{
    return  m_sessionToken;
}

void LoginOutput::SetSessionToken(const boost::optional<std::string> &sessionToken)
{
    m_sessionToken = sessionToken;
}

}