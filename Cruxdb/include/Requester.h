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

#ifndef BASE_REQUESTER_H
#define BASE_REQUESTER_H

#include "Roles.h"
#include "AppCommonDef.h"
#include "User.h"

namespace Cruxdb {

class Requester {
private:
    NON_COPY_NON_MOVE_ABLE(Requester);
    
public:
    Requester() = default;
    virtual ~Requester() = default;
    
    virtual Wt::Dbo::ptr<Cruxdb::User> GetUser() = 0;
    virtual bool HasRole(const std::string &) = 0;
    virtual bool HasRole(const Role &) = 0;
};

}

#endif //BASE_REQUESTER_H
