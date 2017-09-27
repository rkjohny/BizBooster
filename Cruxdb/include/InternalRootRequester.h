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

#ifndef INTERNAL_ROOT_REQUESTER_H
#define INTERNAL_ROOT_REQUESTER_H

#include "Requester.h"


namespace Cruxdb {

class InternalRootRequester : public Requester {
private:
    NON_COPY_NON_MOVE_ABLE(InternalRootRequester);

public:
    InternalRootRequester();
    virtual ~InternalRootRequester() = default;

    Wt::Dbo::ptr<Cruxdb::User> GetUser() override;
    bool HasRole(const std::string &) override;
    bool HasRole(const Role &) override;
    
private:
    Wt::Dbo::ptr<User> m_user;    
};

}

#endif /* INTERNAL_ROOT_REQUESTER_H */