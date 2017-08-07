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


#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "AbstractSerializable.h"
#include "Json.h"
#include "CruxdbDef.h"


namespace Cruxdb {

class AbstractBaseEntity : public Cmarshal::Json::AbstractSerializable {
public:
    AbstractBaseEntity() = default;
    virtual ~AbstractBaseEntity() = default;

    virtual int64_t GetId() const;
    virtual void SetId(int64_t id);

    virtual int GetVersion() const;
    virtual void SetVersion(int v);

protected:
    int64_t m_id;
    int m_version;
    
    REGISTER_GETTER_INCLUDING_BASE_START(Cmarshal::Json::AbstractSerializable )
    GETTER(AbstractBaseEntity, int64_t, COLUMN_ID , &AbstractBaseEntity::GetId),
    GETTER(AbstractBaseEntity, int, COLUMN_VERSION, &AbstractBaseEntity::GetVersion)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(Cmarshal::Json::AbstractSerializable)
    SETTER(AbstractBaseEntity, long, COLUMN_ID, &AbstractBaseEntity::SetId),
    SETTER(AbstractBaseEntity, int, COLUMN_VERSION, &AbstractBaseEntity::SetVersion)
    REGISTER_SETTER_INCLUDING_BASE_END
};


}


#endif