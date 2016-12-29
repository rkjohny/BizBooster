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

#ifndef _SERVICE_FACADE_H_
#define _SERVICE_FACADE_H_

#include "RegisterUserOutput.h"
#include "RegisterUserInput.h"
#include "LogInOutput.h"
#include "LogInInput.h"

namespace Api {

//TODO: Use forward declaration for class RegisterUserInput if needed

class ServiceFacade {
public:
    static web::json::value RegisterUser(RegisterUserInput *input, RegisterUserOutput *output = nullptr);
    
    static web::json::value LogIn(LogInInput *input, LogInOutput *output = nullptr);

private:
    MAKE_STATIC(ServiceFacade);
};
} /* namespace Api */

#endif /* SERVICEFACADE_H_ */
