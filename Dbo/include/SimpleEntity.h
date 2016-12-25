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
#ifndef SIMPLE_ENTITY_H
#define SIMPLE_ENTITY_H

#include "BaseEntity.h"
#include "Status.h"
#include "Json.h"



namespace Dal {

class SimpleEntity : public BaseEntity {
protected:
    Status m_status;

public:
    SimpleEntity() = default;
    virtual ~SimpleEntity() = default;

    virtual Status GetStatus() const;
    virtual void SetStatus(Status m_status);

    REGISTER_GETTER_INCLUDING_BASE_START(BaseEntity)
    GETTER(SimpleEntity, Status, COLUMN_STATUS, &SimpleEntity::GetStatus)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(BaseEntity)
    SETTER(SimpleEntity, Status, COLUMN_STATUS, &SimpleEntity::SetStatus)
    REGISTER_SETTER_INCLUDING_BASE_END

};

}


#endif //SIMPLE_ENTITY_H
