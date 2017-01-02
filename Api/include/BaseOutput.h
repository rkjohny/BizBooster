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

#ifndef BASE_OUTPUT_H
#define BASE_OUTPUT_H

#include "ApiError.h"
#include "Serializable.h"
#include "Json.h"

namespace Api {
using namespace Json;

class BaseOutput : public Serializable {
public:
    BaseOutput() = default;
    virtual ~BaseOutput() = default;

    virtual string ToString() const = 0;
    virtual string Name() const = 0;

    void SetError(const ApiError& error);
    ApiError GetError() const;

    const web::json::value& SerializedValue() const;
    std::string SerializedStr() const;


    web::json::value GetErrorResponse() const;
    std::string GetErrorStr() const;

protected:
    ApiError m_error;

    REGISTER_GETTER_INCLUDING_BASE_START(Serializable)
    GETTER(BaseOutput, ApiError, "error", &BaseOutput::GetError)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(Serializable)
    SETTER(BaseOutput, const ApiError&, "error", &BaseOutput::SetError)
    REGISTER_SETTER_INCLUDING_BASE_END
};

template <class T>
class ApiOutput : public BaseOutput {
public:
    ApiOutput() = default;
    virtual ~ApiOutput() = default;

    const web::json::value& Serialize() override
    {
        m_serializedValue = Json::ToJson<T>(reinterpret_cast<const T*> (this));
        //return Json::ToJson<T>(reinterpret_cast<const T*>(this));
        return m_serializedValue;
    }

    void Deserialize(const web::json::value& jvalue) override
    {
        Json::FromJson<T>(reinterpret_cast<T*> (this), jvalue);
    }

    REGISTER_GETTER_INCLUDING_BASE_START(BaseOutput)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(BaseOutput)
    REGISTER_SETTER_INCLUDING_BASE_END
};

} /* namespace Api */

#endif /* BASE_OUTPUT_H */
