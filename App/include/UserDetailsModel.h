// This may look like C code, but it's really -*- C++ -*-
/*
 * Copyright (C) 2012 Emweb bvba, Kessel-Lo, Belgium.
 *
 * See the LICENSE file for terms of use.
 */
#ifndef USER_DETAILS_MODEL_H_
#define USER_DETAILS_MODEL_H_

#include <Wt/WFormModel.h>
#include <Wt/Auth/Login.h>

#include "WtSession.h"

namespace BizBooster {

    class UserDetailsModel : public Wt::WFormModel {
    public:
        //static const Field FavouritePetField;
        static const Wt::WFormModel::Field FirstName;
        static const Wt::WFormModel::Field LastName;

        UserDetailsModel(Wt::Auth::Login &login);

        void save(Wt::Auth::User &user);

    private:
        Wt::Auth::Login &m_login;
    };

}
#endif // USER_DETAILS_MODEL_H_
