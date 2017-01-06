/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include "LogInWidget.h"
#include "RegistrationView.h"
#include "AppContainer.h"

namespace WebApp {

LogInWidget::LogInWidget(Dal::WtSession &session) : Wt::Auth::AuthWidget(AppContainer::GetAuthService(),
session.GetUserDB(), session.GetLogIn()), m_session(session)
{
}

Wt::WWidget* LogInWidget::CreateRegistrationView(const Wt::Auth::Identity& id)
{
    RegistrationView *w = new RegistrationView(m_session, this);
    Wt::Auth::RegistrationModel *model = createRegistrationModel();

    if (id.isValid())
        model->registerIdentified(id);

    w->setModel(model);
    return w;
}

void LogInWidget::HandleAuthEvent()
{
    if (m_session.GetLogIn().loggedIn()) {
        Wt::log("notice") << "User " << m_session.GetLogIn().user().id()
                << " logged in.";
        //Wt::Dbo::Transaction t(m_session);
        //dbo::ptr<User> user = m_session.GetAuthUser();
        //Wt::log("notice") << "(Favourite pet: " << user->favouritePet << ")";
    } else
        Wt::log("notice") << "User logged out.";
}

}
