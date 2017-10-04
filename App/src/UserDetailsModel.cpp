/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */

#include "UserDetailsModel.h"
#include "User.h"
#include "LibCruxdb.h"
#include "InternalRootRequester.h"
#include "CFReaderFactory.h"
#include "BizBoosterDef.h"
#include "Wt/Mail/Client.h"
#include "Wt/Mail/Message.h"

namespace BizBooster {

    const Wt::WFormModel::Field UserDetailsModel::FirstName = "first-name";
    const Wt::WFormModel::Field UserDetailsModel::LastName = "last-name";


    UserDetailsModel::UserDetailsModel(Wt::Auth::Login &login) : Wt::WFormModel(), m_login(login) {
        addField(FirstName, Wt::WString::tr("first-name-info"));
        addField(LastName, Wt::WString::tr("last-name-info"));
    }

    void UserDetailsModel::save(Wt::Auth::User &authUser) {

        auto userService = Cruxdb::GetUserService();
        auto requester = std::make_shared<Cruxdb::InternalRootRequester>();
        auto &&transaction = Wt::Dbo::Transaction(*userService->GetSession());
        auto user = userService->GetUser(requester, authUser);

        if (user && user.get()) {
            std::string email = authUser.unverifiedEmail();
            //authUser.setEmail(email);
            authUser.setStatus(Wt::Auth::User::Status::Normal);

            user.modify()->SetLogin(email);
            user.modify()->SetFirstName(valueText(FirstName).toUTF8());
            user.modify()->SetLastName(valueText(LastName).toUTF8());
            user.modify()->SetStatus(Cruxdb::Status::V);
            user.modify()->SetRoles(Cruxdb::Role::ROLE_USER);
            //user.modify()->favouritePet = valueText(FavouritePetField).toUTF8();
        }
        transaction.commit();

        //auto configReader = Logfig::CFReaderFactory::GetConfigReader(APP_CONFIG_FILE_NAME);
        Wt::Mail::Message message;
        message.setFrom(Wt::Mail::Mailbox("rezaul@nilavodev.com", "Rezaul Karim"));
        message.addRecipient(Wt::Mail::RecipientType::To, Wt::Mail::Mailbox("rezaul1@nilavodev.com", "Rezaul1 Karim1"));
        message.setSubject("Hey there, koen!");
        message.setBody("That mail client seems to be working.");
        message.addHtmlBody ("<p>"
                                     "<a href=\"http://www.webtoolkit.eu/wt\">That mail client</a>"
                                     " seems to be working just great!</p>");
        Wt::Mail::Client client;
        client.connect("192.168.10.91", 25);
        client.send(message);
    }

}