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

#include "SimpleEntity.h"

namespace Dal {


Status SimpleEntity::GetStatus() const
{
    return m_status;
}

void SimpleEntity::SetStatus(const Status &status)
{
    m_status = status;
    m_statusStr = StatusUtils::ToStr(status);
}

const std::string& SimpleEntity::GetStatusStr() const
{
    return m_statusStr;
}
    
void SimpleEntity::SetStatusStr(const std::string &status)
{
    m_statusStr = status;
    m_status = StatusUtils::ToStatus(status);
}

}