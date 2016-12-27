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

#ifndef PGCONNECTION_H
#define PGCONNECTION_H

#include "AppDef.h"
#include "Disposable.h"
#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/backend/Postgres>

namespace Dal {

class WtPgConnection : public Wt::Dbo::backend::Postgres, public Common::Disposable {
public:
    WtPgConnection() = default;
    virtual ~WtPgConnection();
    void Dispose() override;

private:
    NON_COPY_NON_MOVE_ABLE(WtPgConnection);
};

}

#endif /* PGCONNECTION_H */

