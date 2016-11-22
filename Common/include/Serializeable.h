/**
 * Serializeable.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#ifndef SERIALIZEABLE_H_
#define SERIALIZEABLE_H_

#include <string>

namespace Common {
using namespace std;

class Serializeable
{
public:
    Serializeable();
    virtual ~Serializeable();

    virtual void RegisterClass() = 0;
    virtual string ClassName() const = 0;
};

} /* namespace Api */

#endif /* SERIALIZEABLE_H_ */
