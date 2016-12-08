/**
 * ServiceFacade.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "ServiceFacade.h"
#include "RegisterUserHelper.h"


namespace Api {

web::json::value ServiceFacade::RegisterUser(RegisterUserInput *input)
{
    RegisterUserHelper helper(input);
    //RegisterUserOutput* output = dynamic_cast<RegisterUserOutput*> (helper.Execute());
    web::json::value response = helper.Execute();
    //return output;
    return response;
}

} /* namespace Api */
