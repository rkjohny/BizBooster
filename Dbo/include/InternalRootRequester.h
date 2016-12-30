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

#ifndef INTERNAL_ROOT_REQUESTER_H
#define INTERNAL_ROOT_REQUESTER_H

#include "Requester.h"


namespace Dal {

class InternalRootRequester : public Requester {
protected:
    InternalRootRequester();
    virtual ~InternalRootRequester() = default;

public:
    static InternalRootRequester* GetInstance();
    const User& GetUser() override;
    bool HasRole(const std::string &) override;
    bool HasRole(const Role &) override;
    
private:
    User m_user;
    static InternalRootRequester *m_instance;
    
    NON_COPY_NON_MOVE_ABLE(InternalRootRequester);
};

}

#endif /* INTERNAL_ROOT_REQUESTER_H */