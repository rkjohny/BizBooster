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

#include "BaseOutput.h"

namespace Mocxygen {


void BaseOutput::SetError(const ApiError& error)
{
    m_error = error;
}

ApiError BaseOutput::GetError() const
{
    return m_error;
}

web::json::value BaseOutput::GetErrorResponse() const
{
    auto response = web::json::value::object();
    auto error = web::json::value::object();
    error[U("code")] = web::json::value::number(static_cast<int> (m_error.GetCode()));
    error[U("message")] = web::json::value::string(m_error.GetMessage());
    response[U("error")] = error;
    return response;
}

std::string BaseOutput::GetErrorStr() const
{
    return GetErrorResponse().serialize();
}

const web::json::value& BaseOutput::SerializedValue() const
{
    return m_serializedValue;
}

std::string BaseOutput::SerializedStr() const
{
    return m_serializedValue.serialize();
}

} /* namespace Mocxygen */
