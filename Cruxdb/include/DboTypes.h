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


#ifndef DBO_TYPES_H
#define DBO_TYPES_H

#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>

namespace Cruxdb {

class User;

typedef Wt::Auth::Dbo::AuthInfo<Cruxdb::User> AuthInfo;
typedef Wt::Auth::Dbo::AuthToken<Cruxdb::AuthInfo> AuthToken;
typedef Wt::Auth::Dbo::AuthIdentity< Cruxdb::AuthInfo > AuthIdentity;

typedef Wt::Dbo::collection<Wt::Dbo::ptr<Cruxdb::AuthToken>> AuthTokens;
typedef Wt::Dbo::collection<Wt::Dbo::ptr<Cruxdb::AuthIdentity>> AuthIdentities;

typedef Wt::Auth::Dbo::UserDatabase<Cruxdb::AuthInfo> UserDatabase;

}

#endif /* DBOTYPES_H */

