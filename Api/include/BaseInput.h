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

        virtual web::json::value Process() = 0;

        REGISTER_GETTER_INCLUDING_BASE_START(Serializable)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(Serializable)
        REGISTER_SETTER_INCLUDING_BASE_END
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

        REGISTER_GETTER_INCLUDING_BASE_START(BaseInput)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(BaseInput)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

} /* namespace Api */

#endif /* BASEINPUT_H_ */
