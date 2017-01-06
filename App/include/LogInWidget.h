// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2011 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef AUTH_WIDGET_H
#define AUTH_WIDGET_H

#include "WtSession.h"

#include <Wt/Auth/AuthWidget>

namespace WebApp {

class LogInWidget : public Wt::Auth::AuthWidget
{
public:
  LogInWidget(Wt::Auth::Login &login);

  /* We will use a custom registration view */
  virtual Wt::WWidget* CreateRegistrationView(const Wt::Auth::Identity& id);

  void HandleAuthEvent();
  
private:
  Wt::Auth::Login &m_login;
};

}

#endif // AUTH_WIDGET_H
