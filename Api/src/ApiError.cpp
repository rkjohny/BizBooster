/**
 * ApiError.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "ApiError.h"

namespace Api {

ApiError::ApiError()
{
    //m_code = ApiReturnCode::SUCCESS;
    //m_message = "Success";
}

void ApiError::SetCode(int code)
{
    m_code = code;
}

void ApiError::SetMessage(const string& message)
{
    m_message = message;
}

int ApiError::GetCode() const
{
    return m_code;
}

const string& ApiError::GetMessage() const
{
    return m_message;
}

} /* namespace Api */
