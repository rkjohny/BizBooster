// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef REGISTRATION_VIEW_H_
#define REGISTRATION_VIEW_H_

#include <Wt/Auth/RegistrationWidget.h>
#include <Wt/Auth/Login.h>

#include "UserDetailsModel.h"
#include "WtSession.h"

namespace BizBooster {

class RegistrationView : public Wt::Auth::RegistrationWidget
{
public:
  RegistrationView(Wt::Auth::Login &login, Wt::Auth::AuthWidget *authWidget = nullptr);

  /* specialize to create user details fields */
   std::unique_ptr<Wt::WWidget> createFormWidget(Wt::WFormModel::Field field) override;

protected:
  /* specialize to also validate the user details */
  bool validate() override;

  /* specialize to register user details */
  void registerUserDetails(Wt::Auth::User& user) override;

private:
  UserDetailsModel *m_detailsModel;
  Wt::Auth::Login &m_login;
};

}

#endif // REGISTRATION_VIEW_H_
