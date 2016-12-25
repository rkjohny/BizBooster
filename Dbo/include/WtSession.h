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

#ifndef SESSION_H
#define SESSION_H

#include "AppDef.h"
#include "WtPgConnection.h"
#include <Wt/Dbo/Dbo>

namespace Dal {

class WtSession : public Wt::Dbo::Session {
public:

    WtSession();
    
    virtual ~WtSession() = default;

private:
    NON_COPY_NON_MOVE_ABLE(WtSession);

    WtPgConnection m_connection;
};

}

#endif /* SESSION_H */

