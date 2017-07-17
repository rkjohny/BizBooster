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

#include "LogInInput.h"
#include "Api.h"

namespace Mocxygen {

    void LogInInput::CopyFrom(const LogInInput &&orig) {
        if (orig.m_password) {
            m_password = std::move(orig.m_password);
        }
        if (orig.m_userName) {
            m_userName = std::move(orig.m_userName);
        }
        if (orig.m_rememberMe) {
            m_rememberMe = std::move(orig.m_rememberMe);
        }
        if (orig.m_useFacebookAuth) {
            m_useFacebookAuth = std::move(orig.m_useFacebookAuth);
        }
        if (orig.m_useGoogleAuth) {
            m_useGoogleAuth = std::move(orig.m_useGoogleAuth);
        }
    }

    void LogInInput::CopyFrom(const LogInInput &orig) {
        if (orig.m_password) {
            m_password = *orig.m_password;
        }
        if (orig.m_userName) {
            m_userName = *orig.m_userName;
        }
        if (orig.m_rememberMe) {
            m_rememberMe = *orig.m_rememberMe;
        }
        if (orig.m_useFacebookAuth) {
            m_useFacebookAuth = *orig.m_useFacebookAuth;
        }
        if (orig.m_useGoogleAuth) {
            m_useGoogleAuth = *orig.m_useGoogleAuth;
        }
    }

    std::string LogInInput::Name() const {
        return "LoginInput";
    }

    std::string LogInInput::ToString() const {
        return "LoginInput";
    }

    std::shared_ptr<AbstractBaseOutput> LogInInput::Process(Cruxdb::Requester *requester) {
        return Api::LogIn(requester, this);
    }

    const boost::optional<string> & LogInInput::GetPassword() const {
        return m_password;
    }

    void LogInInput::SetPassword(const boost::optional<std::string> &password) {
        m_password = password;
    }

    const boost::optional<bool> & LogInInput::IsUseFacebookAuth() const {
        return m_useFacebookAuth;
    }

    void LogInInput::SetUseFacebookAuth(const boost::optional<bool> &useFacebookAuth) {
        m_useFacebookAuth = useFacebookAuth;
    }

    const boost::optional<bool> & LogInInput::IsUseGoogleAuth() const {
        return m_useGoogleAuth;
    }

    void LogInInput::SetUseGoogleAuth(const boost::optional<bool> &useGoogleAuth) {
        m_useGoogleAuth = useGoogleAuth;
    }

    const boost::optional<string> & LogInInput::GetUserName() const {
        return m_userName;
    }

    void LogInInput::SetUserName(const boost::optional<std::string> &userName) {
        m_userName = userName;
    }

    const boost::optional<bool> & LogInInput::IsRememberMe() const {
        return m_rememberMe;
    }

    void LogInInput::SetRememberMe(const boost::optional<bool> &rememberMe) {
        m_rememberMe = rememberMe;
    }

}
