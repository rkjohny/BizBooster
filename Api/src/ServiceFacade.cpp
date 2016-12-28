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


namespace Api {

web::json::value ServiceFacade::RegisterUser(std::shared_ptr<RegisterUserInput> input,
        std::shared_ptr<RegisterUserOutput> output)
{
    RegisterUserHelper helper(input, output);
    //RegisterUserOutput* output = dynamic_cast<RegisterUserOutput*> (helper.Execute());
    web::json::value response = helper.Execute();
    //return output;
    return response;
}

} /* namespace Api */
