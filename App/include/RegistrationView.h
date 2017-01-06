// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef REGISTRATION_VIEW_H_
#define REGISTRATION_VIEW_H_

#include <Wt/Auth/RegistrationWidget>

#include "UserDetailsModel.h"
#include "WtSession.h"

namespace WebApp {

class RegistrationView : public Wt::Auth::RegistrationWidget
{
public:
  RegistrationView(Dal::WtSession& session, Wt::Auth::AuthWidget *authWidget = nullptr);

  /* specialize to create user details fields */
  virtual Wt::WWidget *createFormWidget(Wt::WFormModel::Field field);

protected:
  /* specialize to also validate the user details */
  virtual bool validate();

  /* specialize to register user details */
  virtual void registerUserDetails(Wt::Auth::User& user);

private:
  Dal::WtSession& m_session;

  UserDetailsModel *m_detailsModel;
};

}

#endif // REGISTRATION_VIEW_H_
