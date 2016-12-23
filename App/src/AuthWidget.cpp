/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include "AuthWidget.h"
#include "RegistrationView.h"
#include "AuthService.h"
#include "Dao.h"


AuthWidget::AuthWidget(AuthService &authService)
        : Wt::Auth::AuthWidget(AuthService::auth(), authService.GetUsers(), authService.login()),
          m_authService(authService)
{}

Wt::WWidget *AuthWidget::createRegistrationView(const Wt::Auth::Identity &id)
{
    //RegistrationView *w = new RegistrationView(session_, this);
    RegistrationView *w = new RegistrationView(m_authService, this);
    Wt::Auth::RegistrationModel *model = createRegistrationModel();

    if (id.isValid())
        model->registerIdentified(id);

    w->setModel(model);
    return w;
}
