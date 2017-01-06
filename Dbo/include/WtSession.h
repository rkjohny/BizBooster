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
#include "DboTypes.h"

#include <Wt/Dbo/Dbo>
#include <Wt/Auth/Login>

namespace Dal {

class WtSession : public Wt::Dbo::Session, public Common::Disposable {
public:
    void Dispose() override;

    Dal::UserDatabase& GetUserDB();

    static WtSession* GetInstance();
    
protected:
    WtSession();

    virtual ~WtSession();

private:
    NON_COPY_NON_MOVE_ABLE(WtSession);

    WtPgConnection m_connection;

    std::shared_ptr<Dal::UserDatabase> m_users;
    
    static WtSession *m_instance;
};

}

#endif /* SESSION_H */

