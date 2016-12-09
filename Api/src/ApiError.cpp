/**
 * ApiError.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "ApiError.h"

namespace Api {

ApiError::ApiError() : m_code {AppErrorCode::SUCCESS} , m_message (SUCCESS_STR)
{
}

ApiError::ApiError(AppErrorCode code, const std::string &message) : m_code {code} , m_message {message}
{
}

void ApiError::SetCode(AppErrorCode code)
{
    m_code = code;
}

void ApiError::SetMessage(const string& message)
{
    m_message = message;
}

AppErrorCode ApiError::GetCode() const
{
    return m_code;
}

const string& ApiError::GetMessage() const
{
    return m_message;
}

} /* namespace Api */
