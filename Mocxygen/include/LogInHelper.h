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

#ifndef LOGIN_HELPER_H
#define LOGIN_HELPER_H

#include "AbstractApiHelper.h"
#include "LogInInput.h"
#include "LogInOutput.h"
#include "User.h"

namespace Mocxygen {

class LogInHelper : public AbstractApiHelper<LogInInput, LogInOutput> {
private:
    NON_COPY_NON_MOVE_ABLE(LogInHelper);

    Wt::Dbo::ptr<Cruxdb::User> m_user;
    Wt::Dbo::ptr<Cruxdb::AuthInfo> m_authInfo;
    
public:

    LogInHelper(Cruxdb::Requester *requester, LogInInput *input, LogInOutput *output = nullptr) :
    AbstractApiHelper<LogInInput, LogInOutput>(requester, input, output)
    {
    }

    ~LogInHelper() = default;

    void ExecuteHelper() noexcept(false) override;
};

}

#endif /* LOGIN_HELPER_H */

