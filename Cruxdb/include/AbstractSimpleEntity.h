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
#ifndef SIMPLE_ENTITY_H
#define SIMPLE_ENTITY_H

#include "AbstractBaseEntity.h"
#include "Status.h"
#include "Json.h"
#include <string>


namespace Cruxdb {

class AbstractSimpleEntity : public AbstractBaseEntity {
public:
    AbstractSimpleEntity() = default;
    virtual ~AbstractSimpleEntity() = default;

    virtual Status GetStatus() const;
    virtual void SetStatus(const Status &status);
    
    virtual const std::string& GetStatusStr() const;
    virtual void SetStatusStr(const std::string &status);
    
protected:
    std::string m_statusStr;
    
    REGISTER_GETTER_INCLUDING_BASE_START(AbstractBaseEntity)
    GETTER(AbstractSimpleEntity, const std::string&, COLUMN_STATUS, &AbstractSimpleEntity::GetStatusStr)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(AbstractBaseEntity)
    SETTER(AbstractSimpleEntity, const std::string&, COLUMN_STATUS, &AbstractSimpleEntity::SetStatusStr)
    REGISTER_SETTER_INCLUDING_BASE_END

};

}


#endif //SIMPLE_ENTITY_H
