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

    UserDetailsModel::UserDetailsModel(Wt::Auth::Login &login) : Wt::WFormModel(), m_login(login) {

    }

    void UserDetailsModel::save(const Wt::Auth::User &authUser) {
        if (m_login.loggedIn()) {
            auto userService = Cruxdb::GetUserService();
            auto requester = std::make_shared<Cruxdb::InternalRootRequester>();
            auto &&transaction = Wt::Dbo::Transaction(*userService->GetSession());

            auto &authUser = m_login.user();
            auto user = userService->GetUser(requester, authUser);

            if (user && user.get()) {
                //user.modify()->favouritePet = valueText(FavouritePetField).toUTF8();
            }

            transaction.commit();
        }
    }

}