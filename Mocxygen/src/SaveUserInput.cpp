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

#include "SaveUserInput.h"
#include "Api.h"

namespace Mocxygen {

//REGISTER_CLASS_DEC(SaveUserInput, "register_user", 0)
//REGISTER_CLASS_DEC(SaveUserInput, "SaveUserInput", 1)

    void SaveUserInput::CopyFrom(const SaveUserInput &&orig) {
        if (orig.m_email) {
            m_email = std::move(orig.m_email);
        }
        if (orig.m_name) {
            m_name = std::move(orig.m_name);
        }
        if (orig.m_password) {
            m_password = std::move(orig.m_password);
        }
        if (orig.m_roles) {
            m_roles = std::move(orig.m_roles);
        }
        if (orig.m_version) {
            m_version = std::move(orig.m_version);
        }
    }

    void SaveUserInput::CopyFrom(const SaveUserInput &orig) {
        if (orig.m_email) {
            m_email = *orig.m_email;
        }
        if (orig.m_name) {
            m_name = *orig.m_name;
        }
        if (orig.m_password) {
            m_password = *orig.m_password;
        }
        if (orig.m_roles) {
            m_roles = *orig.m_roles;
        }
        if (orig.m_version) {
            m_version = *orig.m_version;
        }
    }


    std::string SaveUserInput::Name() const {
        return "SaveUserInput";
    }

    std::string SaveUserInput::ToString() const {
        return "SaveUserInput";
    }

    std::shared_ptr<AbstractBaseOutput> SaveUserInput::Process(Cruxdb::Requester *requester) {
        return Api::SaveUser(requester, this);
    }

    const boost::optional<std::string> &SaveUserInput::GetEmail() const {
        return m_email;
    }

    void SaveUserInput::SetEmail(const boost::optional<std::string> &email) {
        m_email = email;
    }

    const boost::optional<std::string> &SaveUserInput::GetName() const {
        return m_name;
    }

    void SaveUserInput::SetName(const boost::optional<std::string> &name) {
        m_name = name;
    }

    const boost::optional<std::string> &SaveUserInput::GetRoles() const {
        return m_roles;
    }

    void SaveUserInput::SetRoles(const boost::optional<std::string> &roles) {
        m_roles = roles;
    }

    const boost::optional<int> &SaveUserInput::GetVersion() const {
        return m_version;
    }

    void SaveUserInput::SetVersion(const boost::optional<int> &version) {
        m_version = version;
    }

    const boost::optional<std::string> &SaveUserInput::GetPassword() const {
        return m_password;
    }

    void SaveUserInput::SetPassword(const boost::optional<std::string> &password) {
        m_password = password;
    }

    const boost::optional<std::string> &SaveUserInput::GetStatus() const {
        return m_status;
    }

    void SaveUserInput::SetStatus(const boost::optional<std::string> &status) {
        m_status = status;
    }

    const boost::optional<std::string> &SaveUserInput::GetConfirmPassword() const {
        return m_confirmPassword;
    }

    void SaveUserInput::SetConfirmPassword(const boost::optional<std::string> &confirmPassword) {
        m_confirmPassword = confirmPassword;
    }

    const boost::optional<bool> &SaveUserInput::IsUseFaceBookAuth() const {
        return m_useFaceBookAuth;
    }

    void SaveUserInput::SetUseFaceBookAuth(const boost::optional<bool> &useFaceBookAuth) {
        m_useFaceBookAuth = useFaceBookAuth;
    }

    const boost::optional<bool> &SaveUserInput::IsUseGoogleAuth() const {
        return m_useGoogleAuth;
    }

    void SaveUserInput::SetUseGoogleAuth(const boost::optional<bool> &useGoogleAuth) {
        m_useGoogleAuth = useGoogleAuth;
    }
} /* namespace Mocxygen */

