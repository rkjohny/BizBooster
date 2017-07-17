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

#ifndef LOGGED_IN_HELPER_H
#define LOGGED_IN_HELPER_H

#include "AbstractApiHelper.h"
#include "LoggedInInput.h"
#include "LoggedInOutput.h"
#include "AppCommonDef.h"
#include "LibCruxdb.h"
#include "BaseService.h"
#include "User.h"

namespace Mocxygen {

class LoggedInHelper : public Mocxygen::AbstractApiHelper<Mocxygen::LoggedInInput, Mocxygen::LoggedInOutput> {
public:
    API_HELPER(LoggedInHelper);

    LoggedInHelper(Cruxdb::Requester *requester, LoggedInInput *input, LoggedInOutput *output = nullptr) :
    AbstractApiHelper<LoggedInInput, LoggedInOutput>(requester, input, output)
    {

    }

    virtual ~LoggedInHelper() = default;

    void ExecuteHelper() noexcept(false) override;

private:
    Wt::Dbo::ptr<Cruxdb::User> m_user;
};

}
#endif /* LOGGEDINHELPER_H */

