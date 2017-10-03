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

    const Wt::WFormModel::Field UserDetailsModel::FirstName = "first-name";
    const Wt::WFormModel::Field UserDetailsModel::LastName = "last-name";


    UserDetailsModel::UserDetailsModel(Wt::Auth::Login &login) : Wt::WFormModel(), m_login(login) {
        addField(FirstName, Wt::WString::tr("first-name-info"));
        addField(LastName, Wt::WString::tr("last-name-info"));
    }

    void UserDetailsModel::save(Wt::Auth::User &authUser) {
        //if (m_login.loggedIn()) {
            auto userService = Cruxdb::GetUserService();
            auto requester = std::make_shared<Cruxdb::InternalRootRequester>();
            auto &&transaction = Wt::Dbo::Transaction(*userService->GetSession());

            //const Wt::Auth::User &authUser = m_login.user();
            auto user = userService->GetUser(requester, authUser);

            if (user && user.get()) {
                std::string email = authUser.unverifiedEmail();
                Wt::Auth::Token token = authUser.emailToken();
                authUser.setEmail(email);
                authUser.setStatus(Wt::Auth::User::Status::Normal);

                user.modify()->SetLogin(email);
                user.modify()->SetFirstName(valueText(FirstName).toUTF8());
                user.modify()->SetLastName(valueText(LastName).toUTF8());
                user.modify()->SetStatus(Cruxdb::Status::V);
                user.modify()->SetRoles(Cruxdb::Role::ROLE_USER);
                //user.modify()->favouritePet = valueText(FavouritePetField).toUTF8();
            }
            transaction.commit();
       // }
    }

}