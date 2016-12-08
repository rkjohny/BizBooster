/**
 * ServiceFacade.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
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

    private:
        ServiceFacade() = delete;
    };
} /* namespace Api */

#endif /* SERVICEFACADE_H_ */
