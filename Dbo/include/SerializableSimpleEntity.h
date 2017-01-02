//
// Created by rezaul on 12/11/16.
//

#ifndef SERIALIZABLE_SIMPLE_ENTITY_H
#define SERIALIZABLE_SIMPLE_ENTITY_H

#include "SimpleEntity.h"


namespace Dal {

template <class T>
class SerializableSimpleEntity : public SimpleEntity
{
public:
    SerializableSimpleEntity() = default;
    virtual ~SerializableSimpleEntity() = default;

    const web::json::value& Serialize() override {
        m_serializedValue = Json::ToJson<T>(reinterpret_cast<const T*>(this));
        return m_serializedValue;
    }

    void Deserialize(const web::json::value& jvalue) override {
        Json::FromJson<T>(reinterpret_cast<T*> (this), jvalue);
    }


    REGISTER_GETTER_INCLUDING_BASE_START(SimpleEntity)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(SimpleEntity)
    REGISTER_SETTER_INCLUDING_BASE_END
};

}

#endif //SERIALIZABLE_SIMPLE_ENTITY_H
