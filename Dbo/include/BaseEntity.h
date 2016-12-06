#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include "Serializable.h"
#include "Json.h"


namespace Dal {

class BaseEntity : public Json::Serializable {
public:
    BaseEntity() = default;
    virtual ~BaseEntity() = default;

    long m_id;
    int m_version;

    long GetId() const;
    void SetId(long id);

    int GetVersion() const;
    void SetVersion(int v);

    REGISTER_GETTER_INCLUDING_BASE_START(Json::Serializable)
    GETTER(BaseEntity, long, "id", &BaseEntity::GetId),
    GETTER(BaseEntity, int, "version", &BaseEntity::GetVersion)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(Json::Serializable)
    SETTER(BaseEntity, long, "id", &BaseEntity::SetId),
    SETTER(BaseEntity, int, "version", &BaseEntity::SetVersion)
    REGISTER_SETTER_INCLUDING_BASE_END
};


}


#endif