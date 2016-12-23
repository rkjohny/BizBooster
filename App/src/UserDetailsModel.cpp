/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include "UserDetailsModel.h"
#include "User.h"


const Wt::WFormModel::Field
        UserDetailsModel::FavouritePetField = "favourite-pet";

UserDetailsModel::UserDetailsModel(AuthService &authService, Wt::WObject *parent)
        : Wt::WFormModel(parent),
          m_authService(authService)
{
    addField(FavouritePetField, Wt::WString::tr("favourite-pet-info"));
}

void UserDetailsModel::save(const Wt::Auth::User &authUser)
{
    Wt::Dbo::ptr<Dal::User> user = m_authService.GetLoggedUser(authUser);

    //user.modify()->favouritePet = valueText(FavouritePetField).toUTF8();
}
