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

#include "AbstractSimpleEntity.h"

namespace Cruxdb {


Status AbstractSimpleEntity::GetStatus() const
{
    return StatusUtils::ToStatus(m_statusStr);
}

void AbstractSimpleEntity::SetStatus(const Status &status)
{
    m_statusStr = StatusUtils::ToStr(status);;
}

const std::string& AbstractSimpleEntity::GetStatusStr() const
{
    return m_statusStr;
}
    
void AbstractSimpleEntity::SetStatusStr(const std::string &status)
{
    m_statusStr = status;
}

}