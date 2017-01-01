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

#ifndef LOGGED_IN_HELPER_H
#define LOGGED_IN_HELPER_H

#include "ApiHelper.h"
#include "LoggedInInput.h"
#include "LoggedInOutput.h"
#include "AppDef.h"
#include "Dal.h"
#include "Dao.h"
#include "User.h"

namespace Api {

class LoggedInHelper : public Api::ApiHelper<Api::LoggedInInput, Api::LoggedInOutput> {
public:
    API_HELPER(LoggedInHelper);

    LoggedInHelper(Dal::Requester *requester, LoggedInInput *input, LoggedInOutput *output = nullptr) :
    ApiHelper<LoggedInInput, LoggedInOutput>(requester, input, output)
    {

    }

    virtual ~LoggedInHelper() = default;

    void InitAndValidate() override;

    void CheckPermission() override;

    void ExecuteHelper() override;

private:
    Wt::Dbo::ptr<Dal::User> m_user;
    std::shared_ptr<Dal::Dao> m_dao;
};

}
#endif /* LOGGEDINHELPER_H */

