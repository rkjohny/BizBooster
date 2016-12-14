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

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>
#include <Wt/Dbo/backend/Postgres>

namespace Dal {

class WtPgConnection : public Wt::Dbo::backend::Postgres {
public:
    WtPgConnection() = default;
    virtual ~WtPgConnection() = default;
    
private:
    WtPgConnection(const WtPgConnection& orig);
};

}

#endif /* PGCONNECTION_H */

