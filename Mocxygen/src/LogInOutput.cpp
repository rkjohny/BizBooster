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

#include "LogInOutput.h"
#include "User.h"
#include "LogInHelper.h"

namespace Mocxygen {

void LogInOutput::CopyFrom(const LogInOutput&& orig)
{
    if (orig.m_entity) {
        m_entity = std::move(orig.m_entity);
    }
    if (orig.m_sessionExpiresMsc) {
        m_sessionExpiresMsc = std::move(orig.m_sessionExpiresMsc);
    }
    if (orig.m_sessionToken) {
        m_sessionToken = std::move(orig.m_sessionToken);
    }
}

void LogInOutput::CopyFrom(const LogInOutput& orig)
{
    if (orig.m_entity) {
        m_entity = Wt::Dbo::ptr<Cruxdb::User>(new Cruxdb::User(*orig.m_entity));
    }
    if (orig.m_sessionExpiresMsc) {
        m_sessionExpiresMsc = *orig.m_sessionExpiresMsc;
    }
    if (orig.m_sessionToken) {
        m_sessionToken = *orig.m_sessionToken;
    }
}

std::string LogInOutput::Name() const
{
    return "LogInOutput";
}

std::string LogInOutput::ToString() const
{
    return "LogInOutput";
}

const boost::optional<uint64_t> & LogInOutput::GetSessionExpiresInMS() const
{
    return m_sessionExpiresMsc;
}

void LogInOutput::SetSessionExpires(const boost::optional<uint64_t> &sessionExpiresMsc)
{
    m_sessionExpiresMsc = sessionExpiresMsc;
}

const boost::optional<string> & LogInOutput::GetSessionToken() const
{
    return  m_sessionToken;
}

void LogInOutput::SetSessionToken(const boost::optional<string> &sessionToken)
{
    m_sessionToken = sessionToken;
}

}