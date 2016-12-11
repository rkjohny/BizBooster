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

namespace Dal {

class BaseRequester {
public:
    virtual const User &GetUser() = 0;
    virtual bool HasRole(std::string &&) = 0;
};

}

#endif //BASE_REQUESTER_H
