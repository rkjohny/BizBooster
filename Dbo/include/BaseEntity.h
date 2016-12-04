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


    REGISTER_GETTER_START
    BASE_GETTER(Json::Serializable)
    OWN_GETTER_START
    GETTER(BaseEntity, long, "id", &BaseEntity::GetId)
    OWN_GETTER_END
    REGISTER_GETTER_END

    REGISTER_SETTER_START
    BASE_SETTER(Json::Serializable)
    OWN_SETTER_START
    SETTER(BaseEntity, long, "id", &BaseEntity::SetId)
    OWN_SETTER_END
    REGISTER_SETTER_END
};


}


#endif