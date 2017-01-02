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

#ifndef TINY_JSON_SERIALIZABLE_T_H
#define TINY_JSON_SERIALIZABLE_T_H

#include "Serializable.h"

namespace Json {

    template <class T>
    class SerializableT : public Serializable {
    public:
        SerializableT() = default;
        virtual ~SerializableT() = default;

        const web::json::value& Serialize() override {
            m_serializedValue = Json::ToJson<T>(reinterpret_cast<const T*>(this));
            return m_serializedValue;
        }

        void Deserialize(const web::json::value& jvalue) override {
            Json::FromJson<T>(reinterpret_cast<T*> (this), jvalue);
        }

        REGISTER_GETTER_INCLUDING_BASE_START(Serializable)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(Serializable)
        REGISTER_SETTER_INCLUDING_BASE_END
    };
}


#endif //TINY_JSON_SERIALIZABLE_T_H
