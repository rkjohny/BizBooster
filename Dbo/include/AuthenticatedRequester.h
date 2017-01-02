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

#include "Requester.h"


namespace Api
{
class AppSession;
}

namespace Dal {

class AuthenticatedRequester : public Requester {
    friend class Api::AppSession;
    
private:
    NON_COPY_NON_MOVE_ABLE(AuthenticatedRequester);

    Wt::Dbo::ptr<Dal::User> m_user;
    
protected:
    AuthenticatedRequester() = default;
    
public:
    virtual ~AuthenticatedRequester() = default;

    void SetUser(Wt::Dbo::ptr<Dal::User>&);

    Wt::Dbo::ptr<Dal::User> GetUser() override;
    
    bool HasRole(const std::string &) override;
    bool HasRole(const Role &) override;
};

}


#endif //AUTHENTICATED_REQUESTER_H
