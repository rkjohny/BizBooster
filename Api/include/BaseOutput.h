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
#include "Json.h"

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

    REGISTER_GETTER_START
    REGISTER_GETTER_END

    REGISTER_SETTER_START
    REGISTER_SETTER_END
};

} /* namespace Api */

#endif /* BASEOUTPUT_H_ */
