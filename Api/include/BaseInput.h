/**
 * BaseInput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef BASEINPUT_H_
#define BASEINPUT_H_

#include <string>
#include "Serializeable.h"
#include "Json.h"

namespace Api
{
using namespace std;
using namespace Common;

class BaseOutput;

class BaseInput: public Serializeable
{
public:
    BaseInput();
    virtual ~BaseInput();

    virtual BaseOutput* Process() = 0;
    virtual string ApiName() const = 0;

    REGISTER_GETTER_START
    REGISTER_GETTER_END

    REGISTER_SETTER_START
    REGISTER_SETTER_END
};

} /* namespace Api */

#endif /* BASEINPUT_H_ */
