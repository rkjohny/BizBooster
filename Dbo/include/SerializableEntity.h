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


        REGISTER_GETTER_INCLUDING_BASE_START(AuditableEntity)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AuditableEntity)
        REGISTER_SETTER_INCLUDING_BASE_END
    };
}


#endif //BIZBOOSTER_SERIALIZABLEENTITY_H
