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


#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "Serializable.h"
#include "Json.h"
#include "DboDef.h"


namespace Dal {

class BaseEntity : public Json::Serializable {
public:
    BaseEntity() = default;
    virtual ~BaseEntity() = default;

    int64_t m_id;
    int m_version;

    virtual int64_t GetId() const;
    virtual void SetId(int64_t id);

    virtual int GetVersion() const;
    virtual void SetVersion(int v);

    REGISTER_GETTER_INCLUDING_BASE_START(Json::Serializable)
    GETTER(BaseEntity, int64_t, COLUMN_ID , &BaseEntity::GetId),
    GETTER(BaseEntity, int, COLUMN_VERSION, &BaseEntity::GetVersion)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(Json::Serializable)
    SETTER(BaseEntity, long, COLUMN_ID, &BaseEntity::SetId),
    SETTER(BaseEntity, int, COLUMN_VERSION, &BaseEntity::SetVersion)
    REGISTER_SETTER_INCLUDING_BASE_END
};


}


#endif