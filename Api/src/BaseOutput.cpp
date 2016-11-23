/**
 * BaseOutput.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "BaseOutput.h"

namespace Api {

BaseOutput::BaseOutput()
{
}

BaseOutput::~BaseOutput()
{
}

void BaseOutput::SetError( const ApiError& error )
{
    m_error = error;
}

ApiError BaseOutput::GetError() const
{
    return m_error;
}

} /* namespace Api */
