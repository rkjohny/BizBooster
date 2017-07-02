/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "ApiError.h"
#include "AppException.h"

namespace Mocxygen {

void ApiError::CopyFrom(ApiError &&orig)
{
    SetError(std::move(orig));
}

void ApiError::CopyFrom(const ApiError &orig)
{
    SetError(orig);
}

ApiError::ApiError(AppErrorCode code, const std::string &message) : m_code{code}, m_message{message}
{
}

void ApiError::SetError(const ApiError &error)
{
    m_code = error.m_code;
    m_message = error.m_message;
}

void ApiError::SetError(ApiError &&error)
{
    m_code = std::move(error.m_code);
    m_message = std::move(error.m_message);
}

void ApiError::SetError(Common::AppException &e)
{
    m_code = e.GetCode();
    m_message = e.GetMessage();
}

void ApiError::SetError(Common::AppException &&e)
{
    m_code = std::move(e.GetCode());
    m_message = std::move(e.GetMessage());
}

ApiError& ApiError::operator=(Common::AppException &e)
{
    SetError(e);
    return *this;
}

ApiError& ApiError::operator=(Common::AppException &&e)
{
    SetError(std::move(e));
    return *this;
}


void ApiError::SetError(std::exception &e)
{
    SetError(Common::AppException(e));
}

void ApiError::SetError(std::exception &&e)
{
    SetError(Common::AppException(e));
}

ApiError& ApiError::operator=(std::exception &e)
{
    SetError(Common::AppException(e));
    return *this;
}

ApiError& ApiError::operator=(std::exception &&e)
{
    SetError(Common::AppException(e));
    return *this;
}

void ApiError::SetCode(AppErrorCode code)
{
    m_code = code;
}

void ApiError::SetMessage(const string& message)
{
    m_message = message;
}

void ApiError::SetError(AppErrorCode code, const std::string &message)
{
    m_code = code;
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

web::json::value ApiError::Serialize() const
{
    web::json::value response = web::json::value::object();
    web::json::value error = web::json::value::object();
    error[U("code")] = web::json::value::number(static_cast<int> (m_code));
    error[U("message")] = web::json::value::string(m_message);
    response[U("error")] = error;
    return response;
}

std::string ApiError::ToString() const
{
    return Serialize().serialize();
}

} /* namespace Mocxygen */
