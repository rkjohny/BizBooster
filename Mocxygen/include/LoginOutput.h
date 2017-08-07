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

#include "AbstractBaseOutput.h"
#include "User.h"

namespace Mocxygen {

class LoginOutput : public  AbstractApiGetEntityOutput<LoginOutput, Cruxdb::User> {
public:
    API_OUTPUT(LoginOutput);

    ~LoginOutput() = default;

    const boost::optional<uint64_t> & GetSessionExpiresInMS() const;

    void SetSessionExpires(const boost::optional<uint64_t> &sessionExpiresMsc);

    const boost::optional<string> & GetSessionToken() const;

    void SetSessionToken(const boost::optional<string> &sessionToken);

    REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiOutput<LoginOutput>)
    GETTER(LoginOutput, const boost::optional<string> &, "sessionToken", &LoginOutput::GetSessionToken),
    GETTER(LoginOutput, const boost::optional<uint64_t> &, "sessionExpires", &LoginOutput::GetSessionExpiresInMS)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiOutput<LoginOutput>)
    SETTER(LoginOutput, const boost::optional<string> &, "sessionToken", &LoginOutput::SetSessionToken),
    SETTER(LoginOutput, const boost::optional<uint64_t> &, "sessionExpires", &LoginOutput::SetSessionExpires)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    boost::optional<std::string> m_sessionToken;
    boost::optional<uint64_t> m_sessionExpiresMsc;
};

}

#endif /* LOGIN_OUTPUT_H */

