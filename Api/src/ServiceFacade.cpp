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

#include "ServiceFacade.h"
#include "RegisterUserHelper.h"
#include "LogInInput.h"
#include "LogInOutput.h"
#include "LogInHelper.h"


namespace Api {

web::json::value ServiceFacade::RegisterUser(Dal::BaseRequester *requester, RegisterUserInput *input, RegisterUserOutput *output)
{
    RegisterUserHelper helper(requester, input, output);
    //RegisterUserOutput* output = dynamic_cast<RegisterUserOutput*> (helper.Execute());
    web::json::value response = helper.Execute();
    //return output;
    return response;
}

web::json::value ServiceFacade::LogIn(Dal::BaseRequester *requester, LogInInput *input, LogInOutput *output)
{
    LogInHelper &&helper = LogInHelper(requester, input, output);
    return helper.Execute();
}

} /* namespace Api */
