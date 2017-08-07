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
#include "LoginInput.h"
#include "LoginOutput.h"
#include "LoginHelper.h"
#include "LoggedinHelper.h"


namespace Mocxygen {

std::shared_ptr<SaveUserOutput> Api::SaveUser(Cruxdb::Requester *requester, SaveUserInput *input,
                                                        SaveUserOutput *output)
{
    SaveUserHelper helper(requester, input, output);
    return std::dynamic_pointer_cast<SaveUserOutput, AbstractBaseOutput>(helper.Execute());
}

std::shared_ptr<LoginOutput> Api::LogIn(Cruxdb::Requester *requester, LoginInput *input, LoginOutput *output)
{
    LoginHelper &&helper = LoginHelper(requester, input, output);
    return std::dynamic_pointer_cast<LoginOutput, AbstractBaseOutput>(helper.Execute());
}

std::shared_ptr<LoggedinOutput> Api::UserLoggedIn(Cruxdb::Requester *requester, LoggedinInput *input, LoggedinOutput *output)
{
    LoggedinHelper helper(requester, input, output);
    return std::dynamic_pointer_cast<LoggedinOutput, AbstractBaseOutput>(helper.Execute());
}

} /* namespace Mocxygen */
