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


#include "LoggedinInput.h"
#include "Api.h"

namespace Mocxygen {

    void LoggedinInput::CopyFrom(const LoggedinInput &&orig) {
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

    void LoggedinInput::CopyFrom(const LoggedinInput &orig) {
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


    std::string LoggedinInput::Name() const {
        return "LoggedInInput";
    }

    std::string LoggedinInput::ToString() const {
        return "LoggedInInput";
    }

    std::shared_ptr<AbstractBaseOutput> LoggedinInput::Process(Cruxdb::Requester *requester) {
        return Api::UserLoggedIn(requester, this);
    }


    const boost::optional<std::string> & LoggedinInput::GetSessionToken() const {
        return m_sessionToken;
    }

    void LoggedinInput::SetSessionToken(const boost::optional<std::string> &sessionToken) {
        LoggedinInput::m_sessionToken = sessionToken;
    }

    const boost::optional<uint64_t> & LoggedinInput::GetSessionExpiresInMS() const {
        return m_sessionExpires;
    }

    void LoggedinInput::SetSessionExpires(const boost::optional<uint64_t> &sessionExpires) {
        LoggedinInput::m_sessionExpires = sessionExpires;
    }


}
