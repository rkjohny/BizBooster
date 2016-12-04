#ifndef AUDITABLE_ENTITY_H
#define AUDITABLE_ENTITY_H

#include "BaseEntity.h"
#include "Json.h"


//#include <Wt/Dal/WtSqlTraits>


namespace Dal {
//using namespace Wt::Dal;
class AuditableEntity : public BaseEntity {
public:
    AuditableEntity() = default;
    virtual ~AuditableEntity() = default;

    //WDateTime dateCreated;
    //WDateTime dateLastUpdated;


    REGISTER_ALL_GETTER_START
    BASE_GETTER(BaseEntity)
    OWN_GETTER_START
    OWN_GETTER_END
    REGISTER_ALL_GETTER_END

    REGISTER_ALL_SETTER_START
    BASE_SETTER(BaseEntity)
    OWN_SETTER_START
            OWN_SETTER_END
    REGISTER_ALL_SETTER_END

};
}

#endif