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


    REGISTER_GETTER_INCLUDING_BASE_START(BaseEntity)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(BaseEntity)
    REGISTER_SETTER_INCLUDING_BASE_END
};
}

#endif