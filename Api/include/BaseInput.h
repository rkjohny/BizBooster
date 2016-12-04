/**
 * BaseInput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef _BASE_INPUT_H_
#define _BASE_INPUT_H_

#include <string>
#include "Serializable.h"
#include "Json.h"
#include "BaseOutput.h"

namespace Api {
    using namespace std;
    using namespace Json;

    // TODO: use forward declaration for class BaseOutput if nedded.

    class BaseInput : public Serializable {
    public:
        BaseInput();
        virtual ~BaseInput();

        virtual BaseOutput* Process() = 0;

        REGISTER_GETTER_START
        BASE_GETTER(Serializable)
        OWN_GETTER_START
        OWN_GETTER_END
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        BASE_SETTER(Serializable)
        OWN_SETTER_START
        OWN_SETTER_END
        REGISTER_SETTER_END
    };

    template <class T>
    class ApiInput : public BaseInput {
    public:
        ApiInput() = default;
        virtual ~ApiInput() = default;

        web::json::value Serialize() override {
            return Json::ToJson<T>(dynamic_cast<T*> (this));
        }

        void Deserialize(const web::json::value& jvalue) override {
            Json::FromJson<T>(dynamic_cast<T*> (this), jvalue);
        }

        REGISTER_GETTER_START
        BASE_GETTER(Serializable)
        OWN_GETTER_START
        OWN_GETTER_END
        REGISTER_GETTER_END

        REGISTER_SETTER_START
        BASE_SETTER(Serializable)
        OWN_SETTER_START
        OWN_SETTER_END
        REGISTER_SETTER_END
    };

} /* namespace Api */

#endif /* BASEINPUT_H_ */
