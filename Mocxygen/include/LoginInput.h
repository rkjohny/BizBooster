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


#ifndef LOGIN_INPUT_H
#define LOGIN_INPUT_H

#include <string>
#include "Json.h"
#include "AbstractBaseInput.h"
#include "AppCommonDef.h"

namespace Mocxygen {

class LoginInput : public AbstractApiGetEntityInput<LoginInput> {
public:
    API_INPUT(LoginInput);

    ~LoginInput() = default;

    const boost::optional<std::string> & GetPassword() const;

    void SetPassword(const boost::optional<std::string> &password);

    const boost::optional<bool> & IsUseFacebookAuth() const;

    void SetUseFacebookAuth(const boost::optional<bool> &useFacebookAuth);

    const boost::optional<bool> & IsUseGoogleAuth() const;

    void SetUseGoogleAuth(const boost::optional<bool> &useGoogleAuth);

    const boost::optional<std::string> & GetUserName() const;

    void SetUserName(const boost::optional<std::string> &userName);

    const boost::optional<bool> & IsRememberMe() const;
    void SetRememberMe(const boost::optional<bool> &rememberMe);

    REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiGetEntityInput<LoginInput>)
    GETTER(LoginInput, const boost::optional<std::string>&, "userName", &LoginInput::GetUserName),
    GETTER(LoginInput, const boost::optional<std::string>&, "password", &LoginInput::GetPassword),
    GETTER(LoginInput, const boost::optional<bool>&, "useGoogleAuth", &LoginInput::IsUseFacebookAuth),
    GETTER(LoginInput, const boost::optional<bool>&, "useFacebookAuth", &LoginInput::IsUseGoogleAuth),
    GETTER(LoginInput, const boost::optional<bool>&, "rememberMme", &LoginInput::IsRememberMe)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiGetEntityInput<LoginInput>)
    SETTER(LoginInput, const boost::optional<std::string>&, "userName", &LoginInput::SetUserName),
    SETTER(LoginInput, const boost::optional<std::string>&, "password", &LoginInput::SetPassword),
    SETTER(LoginInput, const boost::optional<bool>&, "useGoogleAuth", &LoginInput::SetUseGoogleAuth),
    SETTER(LoginInput, const boost::optional<bool>&, "useFacebookAuth", &LoginInput::SetUseFacebookAuth),
    SETTER(LoginInput, const boost::optional<bool>&, "rememberMme", &LoginInput::SetRememberMe)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    boost::optional<std::string> m_userName;
    boost::optional<std::string> m_password;
    boost::optional<bool> m_useGoogleAuth;
    boost::optional<bool> m_useFacebookAuth;
    boost::optional<bool> m_rememberMe;
};

}

#endif /* LOGIN_INPUT_H */

