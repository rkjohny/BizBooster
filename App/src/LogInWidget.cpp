/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include "LogInWidget.h"
#include "RegistrationView.h"
#include "AuthServices.h"
#include "Dao.h"
#include "Dal.h"

namespace WebApp {

LogInWidget::LogInWidget(Wt::Auth::Login &login) :
Wt::Auth::AuthWidget(Dal::AuthServices::GetAuthService(), Dal::GetDao()->GetUserDB(), login), m_login(login)
{
}

Wt::WWidget* LogInWidget::CreateRegistrationView(const Wt::Auth::Identity& id)
{
    RegistrationView *w = new RegistrationView(this);
    Wt::Auth::RegistrationModel *model = createRegistrationModel();

    if (id.isValid())
        model->registerIdentified(id);

    w->setModel(model);
    return w;
}

void LogInWidget::HandleAuthEvent()
{
    if (m_login.loggedIn()) {
        Wt::log("notice") << "User " << m_login.user().id()
                << " logged in.";
        //Wt::Dbo::Transaction t(m_session);
        //dbo::ptr<User> user = m_session.GetAuthUser();
        //Wt::log("notice") << "(Favourite pet: " << user->favouritePet << ")";
    } else
        Wt::log("notice") << "User logged out.";
}

}
