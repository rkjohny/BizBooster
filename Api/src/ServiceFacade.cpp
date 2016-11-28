/**
 * ServiceFacade.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "ServiceFacade.h"
#include "RegisterUserHelper.h"
#include "RegisterUserOutput.h"

namespace Api {

RegisterUserOutput* ServiceFacade::RegisterUser(RegisterUserInput* input)
{
    RegisterUserHelper helper(input);
    RegisterUserOutput* output = dynamic_cast<RegisterUserOutput*> (helper.Execute());
    return output;
}

} /* namespace Api */
