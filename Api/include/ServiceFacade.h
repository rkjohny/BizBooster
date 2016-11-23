/**
 * ServiceFacade.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#ifndef SERVICEFACADE_H_
#define SERVICEFACADE_H_

#include "BaseOutput.h"

namespace Api {

//TODO: Forward declaration
class RegisterUserInput;

class ServiceFacade
{
public:
    static BaseOutput* RegisterUser( RegisterUserInput* input );

private:
    ServiceFacade() = delete;
};
} /* namespace Api */

#endif /* SERVICEFACADE_H_ */
