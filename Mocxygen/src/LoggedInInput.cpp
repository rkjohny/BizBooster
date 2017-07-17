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


#include "LoggedInInput.h"
#include "Api.h"

namespace Mocxygen {

    void LoggedInInput::CopyFrom(const LoggedInInput &&orig) {
        if (orig.m_Id) {
            m_Id = std::move(orig.m_Id);
        }
        if (orig.m_sessionExpires) {
            m_sessionExpires = std::move(orig.m_sessionExpires);
        }
        if (orig.m_sessionToken) {
            m_sessionToken = std::move(orig.m_sessionToken);
        }
    }

    void LoggedInInput::CopyFrom(const LoggedInInput &orig) {
        if (orig.m_Id) {
            m_Id = *orig.m_Id;
        }
        if (orig.m_sessionExpires) {
            m_sessionExpires = *orig.m_sessionExpires;
        }
        if (orig.m_sessionToken) {
            m_sessionToken = *orig.m_sessionToken;
        }
    }


    std::string LoggedInInput::Name() const {
        return "LoggedInInput";
    }

    std::string LoggedInInput::ToString() const {
        return "LoggedInInput";
    }

    std::shared_ptr<AbstractBaseOutput> LoggedInInput::Process(Cruxdb::Requester *requester) {
        return Api::UserLoggedIn(requester, this);
    }


    const boost::optional<string> & LoggedInInput::GetSessionToken() const {
        return m_sessionToken;
    }

    void LoggedInInput::SetSessionToken(const boost::optional<string> &sessionToken) {
        LoggedInInput::m_sessionToken = sessionToken;
    }

    const boost::optional<uint64_t> & LoggedInInput::GetSessionExpiresInMS() const {
        return m_sessionExpires;
    }

    void LoggedInInput::SetSessionExpires(const boost::optional<uint64_t> &sessionExpires) {
        LoggedInInput::m_sessionExpires = sessionExpires;
    }


}
