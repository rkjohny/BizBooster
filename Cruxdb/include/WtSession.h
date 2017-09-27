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

#ifndef SESSION_H
#define SESSION_H

#include "AppCommonDef.h"
#include "WtPgConnection.h"
#include "DboTypes.h"
#include "SingleTon.h"

#include <Wt/Dbo/Dbo.h>
#include <Wt/Auth/Login.h>

namespace Cruxdb {

class WtSession : public Wt::Dbo::Session, public Common::Disposable {
private:
    MAKE_SINGLE_TON(WtSession)
    
public:
    void Dispose() override;
    Cruxdb::UserDatabase& GetUserDB();
    
protected:
    WtSession();
    virtual ~WtSession();

private:

    std::shared_ptr<Cruxdb::UserDatabase> m_userDatabase;    
};

}

#endif /* SESSION_H */

