/**
 * ServiceFacade.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef SERVICEFACADE_H_
#define SERVICEFACADE_H_

#include "RegisterUserOutput.h"

namespace Api {

    //TODO: Forward declaration
    class RegisterUserInput;

    class ServiceFacade {
    public:
        static RegisterUserOutput* RegisterUser(RegisterUserInput* input);

    private:
        ServiceFacade() = delete;
    };
} /* namespace Api */

#endif /* SERVICEFACADE_H_ */
