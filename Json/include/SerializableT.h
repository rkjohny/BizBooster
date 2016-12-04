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

        REGISTER_GETTER_INCLUDING_BASE_START(Serializable)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(Serializable)
        REGISTER_SETTER_INCLUDING_BASE_END
    };
}


#endif //BIZBOOSTER_SERIALIZABLET_H
