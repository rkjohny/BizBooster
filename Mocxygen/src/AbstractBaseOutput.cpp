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

#include "AbstractBaseOutput.h"

namespace Mocxygen {


    void AbstractBaseOutput::SetError(const ApiError &error) {
        m_error = error;
    }

    ApiError AbstractBaseOutput::GetError() const {
        return m_error;
    }

    web::json::value AbstractBaseOutput::GetErrorResponse() const {
        auto response = web::json::value::object();
        auto error = web::json::value::object();
        error[U("code")] = web::json::value::number(static_cast<int> (m_error.GetCode()));
        error[U("message")] = web::json::value::string(m_error.GetMessage());
        response[U("error")] = error;
        return response;
    }

    std::string AbstractBaseOutput::GetErrorStr() const {
        return GetErrorResponse().serialize();
    }
    
    const web::json::value& AbstractBaseOutput::SerializedValue() const
    {
        return m_serializedValue;
    }

    std::string AbstractBaseOutput::SerializedStr() const
    {
        return m_serializedValue.serialize();
    }
} /* namespace Mocxygen */
