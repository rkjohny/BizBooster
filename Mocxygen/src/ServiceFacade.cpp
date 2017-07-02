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

#include "ServiceFacade.h"
#include "RegisterUserHelper.h"
#include "LogInInput.h"
#include "LogInOutput.h"
#include "LogInHelper.h"
#include "LoggedInHelper.h"


namespace Mocxygen {

std::shared_ptr<RegisterUserOutput> ServiceFacade::RegisterUser(Cruxdb::Requester *requester, RegisterUserInput *input, RegisterUserOutput *output)
{
    RegisterUserHelper helper(requester, input, output);
    return std::dynamic_pointer_cast<RegisterUserOutput, BaseOutput>(helper.Execute());
}

std::shared_ptr<LogInOutput> ServiceFacade::LogIn(Cruxdb::Requester *requester, LogInInput *input, LogInOutput *output)
{
    LogInHelper &&helper = LogInHelper(requester, input, output);
    return std::dynamic_pointer_cast<LogInOutput, BaseOutput>(helper.Execute());
}

std::shared_ptr<LoggedInOutput> ServiceFacade::UserLoggedIn(Cruxdb::Requester *requester, LoggedInInput *input, LoggedInOutput *output)
{
    LoggedInHelper helper(requester, input, output);
    return std::dynamic_pointer_cast<LoggedInOutput, BaseOutput>(helper.Execute());
}

} /* namespace Mocxygen */
