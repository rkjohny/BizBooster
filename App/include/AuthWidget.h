// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2011 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef AUTH_WIDGET_H_
#define AUTH_WIDGET_H_

#include <Wt/Auth/AuthWidget>

#include "AuthService.h"

class Session;

class AuthWidget : public Wt::Auth::AuthWidget
{
public:
  AuthWidget(AuthService& authService);

  /* We will use a custom registration view */
  virtual Wt::WWidget *createRegistrationView(const Wt::Auth::Identity& id);

private:
  AuthService& m_authService;
};

#endif // AUTH_WIDGET_H_
