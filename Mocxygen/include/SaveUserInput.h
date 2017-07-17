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

#ifndef REGISTER_USER_INPUT_H
#define REGISTER_USER_INPUT_H

#include <string>
#include "AbstractBaseInput.h"
#include "Json.h"
#include "AppCommonDef.h"

namespace Mocxygen {
using namespace std;
using namespace Cmarshal::Json;

class SaveUserInput : public AbstractApiSaveEntityInput<SaveUserInput> {
public:
    API_INPUT(SaveUserInput);
    ~SaveUserInput() = default;

    const boost::optional<string> & GetEmail() const;
    void SetEmail(const boost::optional<std::string> &email);

    const boost::optional<string> & GetName() const;
    void SetName(const boost::optional<std::string> &name);

    const boost::optional<string> & GetRoles() const;
    void SetRoles(const boost::optional<std::string> &roles);

    const boost::optional<int> & GetVersion() const;
    void SetVersion(const boost::optional<int> &version);

    const boost::optional<string> & GetPassword() const;
    void SetPassword(const boost::optional<std::string> &password);

    const boost::optional<string> & GetStatus() const;
    void SetStatus(const boost::optional<std::string> &status);


    const boost::optional<string> & GetConfirmPassword() const;

    void SetConfirmPassword(const boost::optional<std::string>& confirmPassword);

    const boost::optional<bool> & IsUseFaceBookAuth() const;

    void SetUseFaceBookAuth(const boost::optional<bool> &useFaceBookAuth);

    const boost::optional<bool> & IsUseGoogleAuth() const;

    void SetUseGoogleAuth(const boost::optional<bool> &useGoogleAuth);

    REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiSaveEntityInput<SaveUserInput>)
    GETTER(SaveUserInput, const boost::optional<std::string>&, "email", &SaveUserInput::GetEmail),
    GETTER(SaveUserInput, const boost::optional<std::string>&, "name", &SaveUserInput::GetName),
    GETTER(SaveUserInput, const boost::optional<std::string>&, "roles", &SaveUserInput::GetRoles),
    GETTER(SaveUserInput, const boost::optional<std::string>&, "password", &SaveUserInput::GetPassword),
    GETTER(SaveUserInput, const boost::optional<std::string>&, "confirmPassword", &SaveUserInput::GetConfirmPassword),
    GETTER(SaveUserInput, const boost::optional<std::string>&, "status", &SaveUserInput::GetStatus),
    GETTER(SaveUserInput, const boost::optional<int>&, "version", &SaveUserInput::GetVersion),
    GETTER(SaveUserInput, const boost::optional<bool>&, "useGoogleAuth", &SaveUserInput::IsUseGoogleAuth),
    GETTER(SaveUserInput, const boost::optional<bool>&, "useFacebookAuth", &SaveUserInput::IsUseFaceBookAuth)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiSaveEntityInput<SaveUserInput>)
    SETTER(SaveUserInput, const boost::optional<std::string>&, "email", &SaveUserInput::SetEmail),
    SETTER(SaveUserInput, const boost::optional<std::string>&, "name", &SaveUserInput::SetName),
    SETTER(SaveUserInput, const boost::optional<std::string>&, "roles", &SaveUserInput::SetRoles),
    SETTER(SaveUserInput, const boost::optional<std::string>&, "password", &SaveUserInput::SetPassword),
    SETTER(SaveUserInput, const boost::optional<std::string>&, "confirmPassword", &SaveUserInput::SetConfirmPassword),
    SETTER(SaveUserInput, const boost::optional<std::string>&, "status", &SaveUserInput::SetStatus),
    SETTER(SaveUserInput, const boost::optional<int>&, "version", &SaveUserInput::SetVersion),
    SETTER(SaveUserInput, const boost::optional<bool>&, "useGoogleAuth", &SaveUserInput::SetUseGoogleAuth),
    SETTER(SaveUserInput, const boost::optional<bool>&, "useFacebookAuth", &SaveUserInput::SetUseFaceBookAuth)
    REGISTER_SETTER_INCLUDING_BASE_END

    //REGISTER_CLASS_DEF(SaveUserInput, "register_user", 0)
    //REGISTER_CLASS_DEF(SaveUserInput, "SaveUserInput", 1)

private:
    boost::optional<std::string> m_email;
    boost::optional<std::string> m_name;
    boost::optional<std::string> m_roles;
    boost::optional<std::string> m_password;
    boost::optional<std::string> m_confirmPassword;
    boost::optional<int> m_version;
    boost::optional<std::string> m_status;
    boost::optional<bool> m_useGoogleAuth;
    boost::optional<bool> m_useFaceBookAuth;
};

} /* namespace Mocxygen */

#endif /* REGISTER_USER_INPUT_H */
