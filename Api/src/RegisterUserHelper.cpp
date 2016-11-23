/**
 * RegisterUserHelper.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "RegisterUserHelper.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"

namespace Api {

RegisterUserHelper::RegisterUserHelper()
{
}

RegisterUserHelper::RegisterUserHelper( RegisterUserInput* input )
{
    this->m_input = input;
}

void RegisterUserHelper::SetInput( RegisterUserInput* input )
{
    this->m_input = input;
}

void RegisterUserHelper::ValidateInput()
{
}

void RegisterUserHelper::Initialize()
{
}

void RegisterUserHelper::CheckPermission()
{
}

void RegisterUserHelper::ExecuteHelper()
{
    // this must be deleted by caller of execute method
    this->m_output = new RegisterUserOutput();
}

} /* namespace Api */
