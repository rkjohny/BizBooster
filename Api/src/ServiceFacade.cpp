/**
 * ServiceFacade.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "ServiceFacade.h"
#include "RegisterUserHelper.h"
#include "RegisterUserOutput.h"

namespace Api {

BaseOutput* ServiceFacade::RegisterUser( RegisterUserInput* input )
{
    RegisterUserHelper helper( input );
    RegisterUserOutput* output = dynamic_cast< RegisterUserOutput* >( helper.Execute() );
    return output;
}

} /* namespace Api */
