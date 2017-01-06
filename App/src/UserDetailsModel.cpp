/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include "UserDetailsModel.h"
#include "User.h"


namespace WebApp {

const Wt::WFormModel::Field
UserDetailsModel::FavouritePetField = "favourite-pet";

UserDetailsModel::UserDetailsModel(Dal::WtSession& session, Wt::WObject *parent)
: Wt::WFormModel(parent), m_session(session)
{
    //addField(FavouritePetField, Wt::WString::tr("favourite-pet-info"));
}

void UserDetailsModel::save(const Wt::Auth::User& authUser)
{
    //Wt::Dbo::ptr<Dal::User> user = session_.user(authUser);
    //user.modify()->favouritePet = valueText(FavouritePetField).toUTF8();
}

}