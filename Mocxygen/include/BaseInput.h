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

#ifndef _BASE_INPUT_H_
#define _BASE_INPUT_H_

#include <string>
#include "Serializable.h"
#include "Json.h"
#include "BaseOutput.h"
#include "Requester.h"

namespace Mocxygen {
using namespace std;
using namespace Cmarshal::Json;

// TODO: use forward declaration for class BaseOutput if nedded.

class BaseInput : public Serializable {
public:
    BaseInput() = default;
    virtual ~BaseInput() = default;

    virtual std::shared_ptr<BaseOutput> Process(Cruxdb::Requester *requester) = 0;

    virtual string ToString() const = 0;
    virtual string Name() const = 0;

    REGISTER_GETTER_INCLUDING_BASE_START(Serializable)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(Serializable)
    REGISTER_SETTER_INCLUDING_BASE_END

    const web::json::value& SerializedValue() const;
    std::string SerializedStr() const;
};

template <class T>
class ApiInput : public BaseInput {
public:
    ApiInput() = default;
    virtual ~ApiInput() = default;

    const web::json::value& Serialize() override
    {
        m_serializedValue = Cmarshal::Json::ToJson<T>(reinterpret_cast<const T*> (this));
        return m_serializedValue;
    }

    void Deserialize(const web::json::value& jvalue) override
    {
        Cmarshal::Json::FromJson<T>(reinterpret_cast<T*> (this), jvalue);
    }

    REGISTER_GETTER_INCLUDING_BASE_START(BaseInput)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(BaseInput)
    REGISTER_SETTER_INCLUDING_BASE_END
};

} /* namespace Mocxygen */

#endif /* BASEINPUT_H_ */
