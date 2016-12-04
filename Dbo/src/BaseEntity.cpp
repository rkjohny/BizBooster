#include "BaseEntity.h"

using namespace Dal;

long BaseEntity::GetId() const {
    return id;
}

void BaseEntity::SetId(long id) {
    this->id = id;
}
