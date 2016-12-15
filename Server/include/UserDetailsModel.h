// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef USER_DETAILS_MODEL_H_
#define USER_DETAILS_MODEL_H_

#include <Wt/WFormModel>
#include "AuthService.h"

class Session;

class UserDetailsModel : public Wt::WFormModel
{
public:
  static const Field FavouritePetField;

  UserDetailsModel(AuthService& authService, Wt::WObject *parent = 0);

  void save(const Wt::Auth::User& user);

private:
    AuthService& m_authService;
};

#endif // USER_DETAILS_MODEL_H_
