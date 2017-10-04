/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WLineEdit.h>

#include "LogInWidget.h"
#include "RegistrationView.h"
#include "AuthServices.h"
#include "BaseService.h"
#include "LibCruxdb.h"
#include "InternalRootRequester.h"

namespace BizBooster {

LogInWidget::LogInWidget(Wt::Auth::Login &login) :
Wt::Auth::AuthWidget(Cruxdb::AuthServices::GetAuthService(), Cruxdb::GetUserService()->GetUserDB(), login), m_login(login)
{

//    Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("auth_template.xml"));
//    
    setTemplateText(tr("Wt.Auth.template.login"));
//    Wt::WLineEdit *usrName = new Wt::WLineEdit(parent);
//    usrName->setPlaceholderText("Enter your email address");
//    t->bindWidget("user-name", usrName);   
}

std::unique_ptr<Wt::WWidget> LogInWidget::createRegistrationView(const Wt::Auth::Identity& id)
{
    std::unique_ptr<RegistrationView>  registrationVew =  std::make_unique<RegistrationView>(m_login, this);
    std::unique_ptr<Wt::Auth::RegistrationModel> model = createRegistrationModel();

    if (id.isValid())
        model->registerIdentified(id);

    registrationVew->setModel(std::move(model));
    return std::move(registrationVew);
}


}
