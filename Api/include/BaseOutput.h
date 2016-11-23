/**
 * BaseOutput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef BASEOUTPUT_H_
#define BASEOUTPUT_H_

#include "ApiError.h"
#include "Serializeable.h"

namespace Api
{
using namespace Common;

class BaseOutput: public Serializeable
{
public:
    BaseOutput();
    virtual ~BaseOutput();

    void SetError( const ApiError& error );
    ApiError GetError() const;

private:
    ApiError m_error;
};

} /* namespace Api */

#endif /* BASEOUTPUT_H_ */
