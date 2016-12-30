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

#ifndef _BASE_INPUT_H_
#define _BASE_INPUT_H_

#include <string>
#include "Serializable.h"
#include "Json.h"
#include "BaseOutput.h"
#include "BaseRequester.h"

namespace Api {
    using namespace std;
    using namespace Json;

    // TODO: use forward declaration for class BaseOutput if nedded.

    class BaseInput : public Serializable {
    public:
        BaseInput();
        virtual ~BaseInput();

        virtual web::json::value Process(Dal::BaseRequester *requester) = 0;

        virtual string ToString() = 0;
        virtual string Name() = 0;
        
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
            
        web::json::value Serialize() const override {
            return Json::ToJson<T>(reinterpret_cast<const T*>(this));
        }

        void Deserialize(const web::json::value& jvalue) override {
            Json::FromJson<T>(reinterpret_cast<T*> (this), jvalue);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(BaseInput)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(BaseInput)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

} /* namespace Api */

#endif /* BASEINPUT_H_ */
