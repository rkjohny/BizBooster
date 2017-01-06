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


#ifndef DBO_TYPES_H
#define DBO_TYPES_H

#include <Wt/Auth/Dbo/AuthInfo>
#include <Wt/Auth/Dbo/UserDatabase>

namespace Dal {

class User;

typedef Wt::Auth::Dbo::AuthInfo<Dal::User> AuthInfo;
typedef Wt::Auth::Dbo::AuthToken<Dal::AuthInfo> AuthToken;
typedef Wt::Auth::Dbo::AuthIdentity< Dal::AuthInfo > AuthIdentity;

typedef Wt::Dbo::collection<Wt::Dbo::ptr<Dal::AuthToken>> AuthTokens;
typedef Wt::Dbo::collection<Wt::Dbo::ptr<Dal::AuthIdentity>> AuthIdentities;

typedef Wt::Auth::Dbo::UserDatabase<Dal::AuthInfo> UserDatabase;

}

#endif /* DBOTYPES_H */

