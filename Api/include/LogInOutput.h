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
    SERIALIZEABLE(LogInOutput);

    ~LogInOutput() = default;

    const Dal::User& GetUser() const;

    void SetUser(const Dal::User &user);

private:
    Dal::User m_user;

    REGISTER_GETTER_INCLUDING_BASE_START(ApiOutput<LogInOutput>)
    GETTER(LogInOutput, const Dal::User&, "user", &LogInOutput::GetUser)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(ApiOutput<LogInOutput>)
    SETTER(LogInOutput, const Dal::User&, "user", &LogInOutput::SetUser)
    REGISTER_SETTER_INCLUDING_BASE_END
};

}

#endif /* LOGIN_OUTPUT_H */

