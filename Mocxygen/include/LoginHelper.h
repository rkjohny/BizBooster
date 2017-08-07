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

#ifndef LOGIN_HELPER_H
#define LOGIN_HELPER_H

#include "AbstractApiHelper.h"
#include "LoginInput.h"
#include "LoginOutput.h"
#include "User.h"

namespace Mocxygen {

class LoginHelper : public AbstractApiHelper<LoginInput, LoginOutput> {
private:
    API_HELPER(LoginHelper);

    Wt::Dbo::ptr<Cruxdb::User> m_user;
    Wt::Dbo::ptr<Cruxdb::AuthInfo> m_authInfo;
    
public:

    LoginHelper(Cruxdb::Requester *requester, LoginInput *input, LoginOutput *output = nullptr) :
    AbstractApiHelper<LoginInput, LoginOutput>(requester, input, output)
    {
    }

    ~LoginHelper() = default;

    void ExecuteHelper() noexcept(false) override;
};

}

#endif /* LOGIN_HELPER_H */

