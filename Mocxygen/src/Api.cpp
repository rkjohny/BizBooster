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

#include "Api.h"
#include "SaveUserHelper.h"
#include "LogInInput.h"
#include "LogInOutput.h"
#include "LogInHelper.h"
#include "LoggedInHelper.h"


namespace Mocxygen {

std::shared_ptr<SaveUserOutput> Api::SaveUser(Cruxdb::Requester *requester, SaveUserInput *input,
                                                        SaveUserOutput *output)
{
    SaveUserHelper helper(requester, input, output);
    return std::dynamic_pointer_cast<SaveUserOutput, AbstractBaseOutput>(helper.Execute());
}

std::shared_ptr<LogInOutput> Api::LogIn(Cruxdb::Requester *requester, LogInInput *input, LogInOutput *output)
{
    LogInHelper &&helper = LogInHelper(requester, input, output);
    return std::dynamic_pointer_cast<LogInOutput, AbstractBaseOutput>(helper.Execute());
}

std::shared_ptr<LoggedInOutput> Api::UserLoggedIn(Cruxdb::Requester *requester, LoggedInInput *input, LoggedInOutput *output)
{
    LoggedInHelper helper(requester, input, output);
    return std::dynamic_pointer_cast<LoggedInOutput, AbstractBaseOutput>(helper.Execute());
}

} /* namespace Mocxygen */
