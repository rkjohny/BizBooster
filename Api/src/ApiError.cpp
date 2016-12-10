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
