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

class LogInInput : public AbstractApiGetEntityInput<LogInInput> {
public:
    API_INPUT(LogInInput);

    ~LogInInput() = default;

    const boost::optional<string> & GetPassword() const;

    void SetPassword(const boost::optional<std::string> &password);

    const boost::optional<bool> & IsUseFacebookAuth() const;

    void SetUseFacebookAuth(const boost::optional<bool> &useFacebookAuth);

    const boost::optional<bool> & IsUseGoogleAuth() const;

    void SetUseGoogleAuth(const boost::optional<bool> &useGoogleAuth);

    const boost::optional<string> & GetUserName() const;

    void SetUserName(const boost::optional<std::string> &userName);

    const boost::optional<bool> & IsRememberMe() const;
    void SetRememberMe(const boost::optional<bool> &rememberMe);

    REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiGetEntityInput<LogInInput>)
    GETTER(LogInInput, const boost::optional<std::string>&, "userName", &LogInInput::GetUserName),
    GETTER(LogInInput, const boost::optional<std::string>&, "password", &LogInInput::GetPassword),
    GETTER(LogInInput, const boost::optional<bool>&, "useGoogleAuth", &LogInInput::IsUseFacebookAuth),
    GETTER(LogInInput, const boost::optional<bool>&, "useFacebookAuth", &LogInInput::IsUseGoogleAuth),
    GETTER(LogInInput, const boost::optional<bool>&, "rememberMme", &LogInInput::IsRememberMe)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiGetEntityInput<LogInInput>)
    SETTER(LogInInput, const boost::optional<std::string>&, "userName", &LogInInput::SetUserName),
    SETTER(LogInInput, const boost::optional<std::string>&, "password", &LogInInput::SetPassword),
    SETTER(LogInInput, const boost::optional<bool>&, "useGoogleAuth", &LogInInput::SetUseGoogleAuth),
    SETTER(LogInInput, const boost::optional<bool>&, "useFacebookAuth", &LogInInput::SetUseFacebookAuth),
    SETTER(LogInInput, const boost::optional<bool>&, "rememberMme", &LogInInput::SetRememberMe)
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

