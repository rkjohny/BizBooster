/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef WT_USER_SERVICE_H
#define WT_USER_SERVICE_H
#include "AppCommonDef.h"
#include "DboTypes.h"
#include "SingleTon.h"
#include "Requester.h"
#include "BaseService.h"

namespace BizBooster {
    class WtUserService : public Cruxdb::BaseService {
        MAKE_SINGLE_TON(WtUserService)

    public:
        Cruxdb::UserDatabase& GetUserDB();

        Wt::Dbo::ptr<Cruxdb::User> GetUser(std::shared_ptr<Cruxdb::Requester> requester, const Wt::Auth::User &authUser);

    protected:
        WtUserService();
        virtual ~WtUserService();

    private:
        std::shared_ptr<Cruxdb::UserDatabase> m_userDatabase;
    };
}

#endif //WT_USER_SERVICE_H
