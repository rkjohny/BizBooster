//
// Created by rezaul on 12/4/16.
//

#ifndef BIZBOOSTER_SERIALIZABLET_H
#define BIZBOOSTER_SERIALIZABLET_H

#include "Serializable.h"

namespace Json {

    template <class T>
    class SerializableT : public Serializable {
    public:
        SerializableT() = default;
        virtual ~SerializableT() = default;

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
}


#endif //BIZBOOSTER_SERIALIZABLET_H
