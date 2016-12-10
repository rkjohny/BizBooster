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

#ifndef SERIALIZABLE_ENTITY_H
#define SERIALIZABLE_ENTITY_H

#include "AuditableEntity.h"
#include "Json.h"

namespace Dal {

    template <class T>
    class SerializableEntity : public AuditableEntity {
    public:
        SerializableEntity() = default;
        virtual ~SerializableEntity() = default;

        web::json::value Serialize() const override {
            return Json::ToJson<T>(reinterpret_cast<const T*>(this));
        }

        void Deserialize(const web::json::value& jvalue) override {
            Json::FromJson<T>(reinterpret_cast<T*> (this), jvalue);
        }


        REGISTER_GETTER_INCLUDING_BASE_START(AuditableEntity)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AuditableEntity)
        REGISTER_SETTER_INCLUDING_BASE_END
    };
}


#endif //SERIALIZABLE_ENTITY_H
