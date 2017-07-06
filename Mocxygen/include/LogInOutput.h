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

#ifndef LOGIN_OUTPUT_H
#define LOGIN_OUTPUT_H

#include "BaseOutput.h"
#include "User.h"

namespace Mocxygen {

class LogInOutput : public ApiOutput<LogInOutput> {
public:
    API_OUTPUT(LogInOutput);

    ~LogInOutput() = default;

    Wt::Dbo::ptr<Cruxdb::User> GetUser() const;

    void SetUser(Wt::Dbo::ptr<Cruxdb::User> &user);

    uint64_t GetSessionExpires() const;

    void SetSessionExpires(uint64_t sessionExpiresMsc);

    const std::string& GetSessionToken() const;

    void SetSessionToken(const std::string &sessionToken);

    REGISTER_GETTER_INCLUDING_BASE_START(ApiOutput<LogInOutput>)
    GETTER(LogInOutput, Wt::Dbo::ptr<Cruxdb::User>, "user", &LogInOutput::GetUser),
    GETTER(LogInOutput, const std::string&, "session_token", &LogInOutput::GetSessionToken),
    GETTER(LogInOutput, uint64_t, "session_expires", &LogInOutput::GetSessionExpires)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(ApiOutput<LogInOutput>)
    SETTER(LogInOutput, Wt::Dbo::ptr<Cruxdb::User>&, "user", &LogInOutput::SetUser),
    SETTER(LogInOutput, const std::string&, "session_token", &LogInOutput::SetSessionToken),
    SETTER(LogInOutput, uint64_t, "session_expires", &LogInOutput::SetSessionExpires)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    Wt::Dbo::ptr<Cruxdb::User> m_user;

    std::string m_sessionToken;
    uint64_t m_sessionExpiresMsc;
};

}

#endif /* LOGIN_OUTPUT_H */

