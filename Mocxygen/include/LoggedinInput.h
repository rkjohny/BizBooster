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

#ifndef LOGGED_IN_INPUT_H
#define LOGGED_IN_INPUT_H

#include "AbstractBaseInput.h"
#include "AppCommonDef.h"

namespace Mocxygen {

class LoggedinInput : public AbstractApiGetEntityInput<LoggedinInput> {
public:
    API_INPUT(LoggedinInput);

    virtual ~LoggedinInput() = default;

    const boost::optional<string> & GetSessionToken() const;

    void SetSessionToken(const boost::optional<string> &sessionToken);

    const boost::optional<uint64_t> & GetSessionExpiresInMS() const;

    void SetSessionExpires(const boost::optional<uint64_t> &sessionExpires);

    REGISTER_GETTER_INCLUDING_BASE_START(AbstractApiGetEntityInput<LoggedinInput>)
    GETTER(LoggedinInput,  const boost::optional<uint64_t> &, "sessionExpires", &LoggedinInput::GetSessionExpiresInMS),
    GETTER(LoggedinInput,  const boost::optional<string> &, "sessionToken", &LoggedinInput::GetSessionToken)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(AbstractApiGetEntityInput<LoggedinInput>)
    SETTER(LoggedinInput,  const boost::optional<uint64_t>&, "sessionExpires", &LoggedinInput::SetSessionExpires),
    SETTER(LoggedinInput,  const boost::optional<string>&, "sessionToken", &LoggedinInput::SetSessionToken)
    REGISTER_SETTER_INCLUDING_BASE_END

private:
    boost::optional<std::string> m_sessionToken;
    boost::optional<uint64_t> m_sessionExpires;
};

}
#endif /* LOGGEDIN_INPUT_H */

