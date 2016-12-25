/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "LogInHelper.h"

namespace Api {

LogInHelper::LogInHelper()
{
}

LogInHelper::~LogInHelper()
{
}

LogInHelper::LogInHelper(LogInInput *input)
{
    m_input = input;
}

LogInHelper::LogInHelper(LogInInput &input)
{
    m_input = &input;
}

void LogInHelper::SetInput(LogInInput *in)
{
    m_input = in;
}

void LogInHelper::SetInput(LogInInput &in)
{
    m_input = &in;
}

void LogInHelper::InitAndValidate()
{
}

void LogInHelper::CheckPermission()
{
}

void LogInHelper::ExecuteHelper()
{
}

}