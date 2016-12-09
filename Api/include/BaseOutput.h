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

        web::json::value Serialize() override {
            return Json::ToJson<T>(dynamic_cast<T*> (this));
        }

        void Deserialize(const web::json::value& jvalue) override {
            Json::FromJson<T>(dynamic_cast<T*> (this), jvalue);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(BaseOutput)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(BaseOutput)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

} /* namespace Api */

#endif /* BASEOUTPUT_H_ */
