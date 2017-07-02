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

#include "BaseEntity.h"

using namespace Cruxdb;

long BaseEntity::GetId() const {
    return m_id;
}

void BaseEntity::SetId(int64_t id) {
    this->m_id = id;
}

int BaseEntity::GetVersion() const
{
    return m_version;
}

void BaseEntity::SetVersion(int v)
{
    m_version = v;
}

