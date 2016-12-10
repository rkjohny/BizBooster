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

namespace Api {

    //TODO: Use forward declaration for class RegisterUserInput if needed

    class ServiceFacade {
    public:
        static web::json::value RegisterUser(RegisterUserInput *input);
        static web::json::value RegisterUser(RegisterUserInput &input);

    private:
        ServiceFacade() = delete;
    };
} /* namespace Api */

#endif /* SERVICEFACADE_H_ */
