/**
 * BaseInput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#ifndef BASEINPUT_H_
#define BASEINPUT_H_

#include <string>
#include "Serializeable.h"

namespace Api {
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
};

} /* namespace Api */

#endif /* BASEINPUT_H_ */
