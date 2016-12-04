/**
 * BaseOutput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef BASEOUTPUT_H_
#define BASEOUTPUT_H_

#include "ApiError.h"
#include "Serializable.h"
#include "Json.h"

namespace Api {
    using namespace Json;

    class BaseOutput : public Serializable {
    public:
        BaseOutput();
        virtual ~BaseOutput();

        void SetError(const ApiError& error);
        ApiError GetError() const;

    private:
        ApiError m_error;

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
    class ApiOutput : public BaseOutput {
    public:
        ApiOutput() = default;
        virtual ~ApiOutput() = default;

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

#endif /* BASEOUTPUT_H_ */
