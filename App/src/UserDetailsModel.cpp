/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include "UserDetailsModel.h"
#include "User.h"
#include "LibCruxdb.h"
#include "InternalRootRequester.h"


namespace BizBooster {

const Wt::WFormModel::Field
UserDetailsModel::FavouritePetField = "favourite-pet";

UserDetailsModel::UserDetailsModel(Wt::Auth::Login &login, Wt::WObject *parent) :
Wt::WFormModel(parent), m_login(login)
{
    addField(FavouritePetField, Wt::WString::tr("favourite-pet-info"));
}

void UserDetailsModel::save(const Wt::Auth::User& authUser)
{
    if (m_login.loggedIn()) {
        auto dao = Cruxdb::GetDao();
        auto requester = Cruxdb::InternalRootRequester::GetInstance();
        auto transaction = dao->BeginTransaction(requester);

        auto &authUser = m_login.user();
        auto user = dao->GetUser(requester, authUser);
        
        if (user && user.get()) {
            //user.modify()->favouritePet = valueText(FavouritePetField).toUTF8();
        }

        dao->CommitTransaction(requester, transaction);
    }
}

}