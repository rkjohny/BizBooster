/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#include "RegistrationView.h"
#include "UserDetailsModel.h"

#include <Wt/WLineEdit>

namespace WebApp {

RegistrationView::RegistrationView(Wt::Auth::AuthWidget *authWidget) : Wt::Auth::RegistrationWidget(authWidget)
{
    setTemplateText(tr("template.registration"));
    m_detailsModel = new UserDetailsModel(this);

    updateView(m_detailsModel);
}

Wt::WWidget *RegistrationView::createFormWidget(Wt::WFormModel::Field field)
{
    if (field == UserDetailsModel::FavouritePetField)
        return new Wt::WLineEdit();
    else
        return Wt::Auth::RegistrationWidget::createFormWidget(field);
}

bool RegistrationView::validate()
{
    bool result = Wt::Auth::RegistrationWidget::validate();

    updateModel(m_detailsModel);
    if (!m_detailsModel->validate())
        result = false;
    updateView(m_detailsModel);

    return result;
}

void RegistrationView::registerUserDetails(Wt::Auth::User& user)
{
    m_detailsModel->save(user);
}

}