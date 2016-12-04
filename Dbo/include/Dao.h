#ifndef ABSTRACT_DAO_H
#define ABSTRACT_DAO_H

#include <string>
#include "Connector.h"
#include "User.h"


namespace Dal {
class Dao {

protected:
    Dao();

    Dao(Dao &);

    virtual ~Dao();

public:
    static Dao *GetInstance();

    virtual void RegisterUser(Connector &connector, User &loggedUser, User &newUser) = 0;

    virtual User *GetUser(Connector &connector, User &loggedUser, std::string email) = 0;

};
}


#endif