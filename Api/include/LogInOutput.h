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

#ifndef LOGIN_OUTPUT_H
#define LOGIN_OUTPUT_H

#include "BaseOutput.h"
#include "User.h"

namespace Api {

class LogInOutput : public ApiOutput<LogInOutput> {
public:
    API_OUTPUT(LogInOutput);

    ~LogInOutput() = default;

    const Dal::User& GetUser() const;

    void SetUser(const Dal::User &user);
    
    uint64_t GetSessionExpires() const;

    void SetSessionExpires(const uint64_t &sessionExpiresMsc);

    const std::string& GetSessionToken() const;

    void SetSessionToken(const std::string &sessionToken);

private:
    Dal::User m_user;
    
    std::string m_sessionToken;
    uint64_t m_sessionExpiresMsc;

    REGISTER_GETTER_INCLUDING_BASE_START(ApiOutput<LogInOutput>)
    GETTER(LogInOutput, const Dal::User&, "user", &LogInOutput::GetUser)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(ApiOutput<LogInOutput>)
    SETTER(LogInOutput, const Dal::User&, "user", &LogInOutput::SetUser)
    REGISTER_SETTER_INCLUDING_BASE_END
};

}

#endif /* LOGIN_OUTPUT_H */

