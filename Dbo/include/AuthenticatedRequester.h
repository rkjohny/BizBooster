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

#ifndef AUTHENTICATED_REQUESTER_H
#define AUTHENTICATED_REQUESTER_H

#include "User.h"
#include "BaseRequester.h"


namespace Dal {

class AuthenticatedRequester : public BaseRequester {
private:
    User m_user;

public:
    AuthenticatedRequester() = default;
    AuthenticatedRequester(User &&user);
    AuthenticatedRequester(const User &user);

    void SetUser(User &&);
    void SetUser(const User&);

    const User &GetUser() override;
    bool HasRole(std::string &&) override;
};

}


#endif //AUTHENTICATED_REQUESTER_H
