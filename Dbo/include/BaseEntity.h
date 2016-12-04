#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "Serializable.h"
#include "Json.h"


namespace Dal {

class BaseEntity : public Json::Serializable {
public:
    BaseEntity() = default;
    virtual ~BaseEntity() = default;


    long id;

    long GetId() const;

    void SetId(long id);

    REGISTER_GETTER_INCLUDING_BASE_START(Json::Serializable)
    GETTER(BaseEntity, long, "id", &BaseEntity::GetId)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(Json::Serializable)
    SETTER(BaseEntity, long, "id", &BaseEntity::SetId)
    REGISTER_SETTER_INCLUDING_BASE_END
};


}


#endif