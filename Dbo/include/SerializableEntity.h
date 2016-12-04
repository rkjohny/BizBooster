//
// Created by rezaul on 12/4/16.
//

#ifndef BIZBOOSTER_SERIALIZABLEENTITY_H
#define BIZBOOSTER_SERIALIZABLEENTITY_H

#include "AuditableEntity.h"
#include "Json.h"

namespace Dal {

    template <class T>
    class SerializableEntity : public AuditableEntity {
    public:
        SerializableEntity() = default;
        virtual ~SerializableEntity() = default;

        web::json::value Serialize() override {
            return Json::ToJson<T>(dynamic_cast<T*> (this));
        }

        void Deserialize(const web::json::value& jvalue) override {
            Json::FromJson<T>(dynamic_cast<T*> (this), jvalue);
        }


        REGISTER_ALL_GETTER_START
        BASE_GETTER(AuditableEntity)
        OWN_GETTER_START
                OWN_GETTER_END
        REGISTER_ALL_GETTER_END

        REGISTER_ALL_SETTER_START
        BASE_SETTER(AuditableEntity)
        OWN_SETTER_START
                OWN_SETTER_END
        REGISTER_ALL_SETTER_END
    };
}


#endif //BIZBOOSTER_SERIALIZABLEENTITY_H
