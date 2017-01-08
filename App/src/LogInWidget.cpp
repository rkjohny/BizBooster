/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WLineEdit>

#include "LogInWidget.h"
#include "RegistrationView.h"
#include "AuthServices.h"
#include "Dao.h"
#include "Dal.h"
#include "InternalRootRequester.h"

namespace WebApp {

LogInWidget::LogInWidget(Wt::WContainerWidget *parent, Wt::Auth::Login &login) :
Wt::Auth::AuthWidget(Dal::AuthServices::GetAuthService(), Dal::GetDao()->GetUserDB(), login), m_login(login)
{
//    Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("auth_template.xml"));
//    
//    setTemplateText(tr("Wt.Auth.template.login"));
//    Wt::WLineEdit *usrName = new Wt::WLineEdit(parent);
//    usrName->setPlaceholderText("Enter your email address");
//    t->bindWidget("user-name", usrName);   
}

Wt::WWidget* LogInWidget::createRegistrationView(const Wt::Auth::Identity& id)
{
    RegistrationView *w = new RegistrationView(m_login, this);
    Wt::Auth::RegistrationModel *model = createRegistrationModel();

    if (id.isValid())
        model->registerIdentified(id);

    w->setModel(model);
    return w;
}


}
