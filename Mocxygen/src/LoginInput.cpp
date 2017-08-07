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

#include "LoginInput.h"
#include "Api.h"

namespace Mocxygen {

    void LoginInput::CopyFrom(const LoginInput &&orig) {
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

    void LoginInput::CopyFrom(const LoginInput &orig) {
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

    std::string LoginInput::Name() const {
        return "LoginInput";
    }

    std::string LoginInput::ToString() const {
        return "LoginInput";
    }

    std::shared_ptr<AbstractBaseOutput> LoginInput::Process(Cruxdb::Requester *requester) {
        return Api::LogIn(requester, this);
    }

    const boost::optional<string> & LoginInput::GetPassword() const {
        return m_password;
    }

    void LoginInput::SetPassword(const boost::optional<std::string> &password) {
        m_password = password;
    }

    const boost::optional<bool> & LoginInput::IsUseFacebookAuth() const {
        return m_useFacebookAuth;
    }

    void LoginInput::SetUseFacebookAuth(const boost::optional<bool> &useFacebookAuth) {
        m_useFacebookAuth = useFacebookAuth;
    }

    const boost::optional<bool> & LoginInput::IsUseGoogleAuth() const {
        return m_useGoogleAuth;
    }

    void LoginInput::SetUseGoogleAuth(const boost::optional<bool> &useGoogleAuth) {
        m_useGoogleAuth = useGoogleAuth;
    }

    const boost::optional<string> & LoginInput::GetUserName() const {
        return m_userName;
    }

    void LoginInput::SetUserName(const boost::optional<std::string> &userName) {
        m_userName = userName;
    }

    const boost::optional<bool> & LoginInput::IsRememberMe() const {
        return m_rememberMe;
    }

    void LoginInput::SetRememberMe(const boost::optional<bool> &rememberMe) {
        m_rememberMe = rememberMe;
    }

}
