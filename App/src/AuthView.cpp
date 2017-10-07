/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include <Wt/WLineEdit.h>
#include "AuthView.h"
#include "RegistrationView.h"
#include "WtAuthServices.h"
#include "BaseService.h"
#include "WtUserService.h"

namespace BizBooster {

    AuthView::AuthView(Wt::Auth::Login &login) :
            Wt::Auth::AuthWidget(WtAuthServices::GetWtAuthService(),
                                 Common::SingleTon<WtUserService>::GetInstance()->GetUserDB(), login), m_login(login) {

        //Wt::WTemplate *t = new Wt::WTemplate(Wt::WString::tr("Wt.Auth.template.login"));

        setTemplateText(tr("Wt.Auth.template.login"));
        //Wt::WLineEdit *usrName = new Wt::WLineEdit(parent);
        //usrName->setPlaceholderText("Enter your email address");
        //t->bindWidget("user-name", usrName);

        model()->addOAuth(WtAuthServices::GetWtGoogleOauthService());
        model()->addPasswordAuth(&WtAuthServices::GetWtPasswordService());

        setRegistrationEnabled(true);

        icons = bindWidget("icons", std::make_unique<Wt::WIcon>("resources/oauth-google.png"));
        icons->clicked().connect(WtAuthServices::GetWtGoogleOauthProcess(), &Wt::Auth::OAuthProcess::startAuthenticate);

        processEnvironment();
    }

    std::unique_ptr<Wt::WWidget> AuthView::createRegistrationView(const Wt::Auth::Identity &id) {
        std::unique_ptr<RegistrationView> registrationVew = std::make_unique<RegistrationView>(m_login, this);
        std::unique_ptr<Wt::Auth::RegistrationModel> model = createRegistrationModel();

        if (id.isValid())
            model->registerIdentified(id);

        registrationVew->setModel(std::move(model));
        return std::move(registrationVew);
    }
}
