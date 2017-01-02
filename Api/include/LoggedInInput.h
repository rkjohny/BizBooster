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

#ifndef LOGGED_IN_INPUT_H
#define LOGGED_IN_INPUT_H

#include "BaseInput.h"
#include "AppDef.h"

namespace Api {

class LoggedInInput : public ApiInput<LoggedInInput> {
public:
    API_INPUT(LoggedInInput);

    virtual ~LoggedInInput() = default;

    uint64_t GetSessionExpires() const;

    void SetSessionExpires(uint64_t expires);

    const std::string& GetSessionToken() const;

    void SetSessionToken(const std::string &sessionToken);

    uint64_t GetUserId() const;

    void SetUserId(uint64_t userId);
    

    REGISTER_GETTER_INCLUDING_BASE_START(ApiInput<LoggedInInput>)
    GETTER(LoggedInInput, uint64_t, "user_id", &LoggedInInput::GetUserId),
    GETTER(LoggedInInput, uint64_t, "session_expires", &LoggedInInput::GetSessionExpires),
    GETTER(LoggedInInput, const std::string&, "session_token", &LoggedInInput::GetSessionToken)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(ApiInput<LoggedInInput>)
    SETTER(LoggedInInput, uint64_t, "user_id", &LoggedInInput::SetUserId),
    SETTER(LoggedInInput, uint64_t, "session_expires", &LoggedInInput::SetSessionExpires),
    SETTER(LoggedInInput, const std::string&, "session_token", &LoggedInInput::SetSessionToken)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    uint64_t m_userId;
    std::string m_sessionToken;
    uint64_t m_sessionExpires;
};

}
#endif /* LOGGEDIN_INPUT_H */

