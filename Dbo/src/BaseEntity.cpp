#include "BaseEntity.h"

using namespace Dal;

long BaseEntity::GetId() const {
    return m_id;
}

void BaseEntity::SetId(long id) {
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

