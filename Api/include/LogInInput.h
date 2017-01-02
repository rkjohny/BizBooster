/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
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
#include "BaseInput.h"
#include "AppDef.h"

namespace Api {

class LogInInput : public ApiInput<LogInInput> {
public:
    API_INPUT(LogInInput);

    ~LogInInput() = default;

    const std::string& GetPassword() const;

    void SetPassword(const std::string &password);

    bool IsUseFacebookAuth() const;

    void SetUseFacebookAuth(bool useFacebookAuth);

    bool IsUseGoogleAuth() const;

    void SetUseGoogleAuth(bool useGoogleAuth);

    const std::string& GetUserName() const;

    void SetUserName(const std::string &userName);

    bool IsRememberMe() const;
    void SetRememberMe(bool rememberMe);

    REGISTER_GETTER_INCLUDING_BASE_START(ApiInput<LogInInput>)
    GETTER(LogInInput, const std::string&, "user_name", &LogInInput::GetUserName),
    GETTER(LogInInput, const std::string&, "password", &LogInInput::GetPassword),
    GETTER(LogInInput, bool, "use_google_auth", &LogInInput::IsUseFacebookAuth),
    GETTER(LogInInput, bool, "use_facebook_auth", &LogInInput::IsUseGoogleAuth),
    GETTER(LogInInput, bool, "remember_me", &LogInInput::IsRememberMe)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(ApiInput<LogInInput>)
    SETTER(LogInInput, const std::string&, "user_name", &LogInInput::SetUserName),
    SETTER(LogInInput, const std::string&, "password", &LogInInput::SetPassword),
    SETTER(LogInInput, bool, "use_google_auth", &LogInInput::SetUseGoogleAuth),
    SETTER(LogInInput, bool, "use_facebook_auth", &LogInInput::SetUseFacebookAuth),
    SETTER(LogInInput, bool, "remember_me", &LogInInput::SetRememberMe)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    std::string m_userName;
    std::string m_password;
    bool m_useGoogleAuth;
    bool m_useFacebookAuth;
    bool m_rememberMe;
};

}

#endif /* LOGIN_INPUT_H */

