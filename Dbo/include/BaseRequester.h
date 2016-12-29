/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef BASE_REQUESTER_H
#define BASE_REQUESTER_H

#include "Roles.h"
#include "AppDef.h"
#include <memory>

namespace Dal {

class BaseRequester {
private:
    NON_COPY_NON_MOVE_ABLE(BaseRequester);
    
public:
    BaseRequester() = default;
    virtual ~BaseRequester() = default;
    
    virtual const std::shared_ptr<User> GetUser() = 0;
    virtual bool HasRole(const std::string &) = 0;
    virtual bool HasRole(const Role &) = 0;
};

}

#endif //BASE_REQUESTER_H
