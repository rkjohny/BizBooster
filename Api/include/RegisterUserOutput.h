/**
 * RegisterUserOutput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef REGISTERUSEROUTPUT_H_
#define REGISTERUSEROUTPUT_H_

#include "BaseOutput.h"

namespace Api
{
using namespace std;
using namespace Json;

class RegisterUserOutput: public ApiOutput<RegisterUserOutput>
{
public:
    RegisterUserOutput();
    ~RegisterUserOutput();

private:
    REGISTER_ALL_GETTER_START
    BASE_GETTER(ApiOutput<RegisterUserOutput>)
    OWN_GETTER_START
    OWN_GETTER_END
    REGISTER_ALL_GETTER_END

    REGISTER_ALL_SETTER_START
    BASE_SETTER(ApiOutput<RegisterUserOutput>)
    OWN_SETTER_START
    OWN_SETTER_END
    REGISTER_ALL_SETTER_END
};

} /* namespace Api */

#endif /* REGISTERUSEROUTPUT_H_ */
