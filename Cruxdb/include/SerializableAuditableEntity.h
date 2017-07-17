/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef SERIALIZABLE_ENTITY_H
#define SERIALIZABLE_ENTITY_H

#include "AbstractAuditableEntity.h"
#include "Json.h"

namespace Cruxdb {

    template <class T>
    class SerializableAuditableEntity : public AbstractAuditableEntity {
    public:
        SerializableAuditableEntity() = default;
        virtual ~SerializableAuditableEntity() = default;

        web::json::value& Serialize() override {
            m_serializedValue = Cmarshal::Json::ToJson<T>(reinterpret_cast<const T*>(this));
            return m_serializedValue;
        }

        void Deserialize(const web::json::value& jvalue) override {
            Cmarshal::Json::FromJson<T>(reinterpret_cast<T*> (this), jvalue);
        }


        REGISTER_GETTER_INCLUDING_BASE_START(AbstractAuditableEntity)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(AbstractAuditableEntity)
        REGISTER_SETTER_INCLUDING_BASE_END
    };
}


#endif //SERIALIZABLE_ENTITY_H
