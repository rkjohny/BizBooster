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

#ifndef PGCONNECTION_H
#define PGCONNECTION_H

#include "AppCommonDef.h"
#include "Disposable.h"
#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>
#include <Wt/Dbo/backend/Postgres.h>

namespace Cruxdb {

class WtPgConnection : public Wt::Dbo::backend::Postgres, public Common::Disposable {
private:
    NON_COPY_NON_MOVE_ABLE(WtPgConnection);
    
public:
    WtPgConnection() = default;
    virtual ~WtPgConnection();
    void Dispose() override;
};

}

#endif /* PGCONNECTION_H */

