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
#include "LoggedinInput.h"
#include "LoggedinOutput.h"
#include "AppCommonDef.h"
#include "LibCruxdb.h"
#include "BaseService.h"
#include "User.h"

namespace Mocxygen {

class LoggedinHelper : public Mocxygen::AbstractApiHelper<Mocxygen::LoggedinInput, Mocxygen::LoggedinOutput> {
private:
    API_HELPER(LoggedinHelper);
    
public:
    LoggedinHelper(Cruxdb::Requester *requester, LoggedinInput *input, LoggedinOutput *output = nullptr) :
    AbstractApiHelper<LoggedinInput, LoggedinOutput>(requester, input, output)
    {

    }

    virtual ~LoggedinHelper() = default;

    void ExecuteHelper() noexcept(false) override;

private:
    Wt::Dbo::ptr<Cruxdb::User> m_user;
};

}
#endif /* LOGGEDINHELPER_H */

