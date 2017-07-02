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



#ifndef REGISTER_USER_HELPER_H
#define REGISTER_USER_HELPER_H

#include "ApiHelper.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"

namespace Mocxygen {

//TODO: Use forrward declaration of class RegisterUserInput if needed.

class RegisterUserHelper : public ApiHelper <RegisterUserInput, RegisterUserOutput> {
private:
    NON_COPY_NON_MOVE_ABLE(RegisterUserHelper);
    
    Wt::Dbo::ptr<Cruxdb::User> m_user;

public:
    ~RegisterUserHelper() = default;

    RegisterUserHelper(Cruxdb::Requester *requester, RegisterUserInput *input, RegisterUserOutput *output = nullptr) :
    ApiHelper<RegisterUserInput, RegisterUserOutput>(requester, input, output)
    {
    }
    
    void InitAndValidate() override;

    void CheckPermission() override;

    void ExecuteHelper() override;
};

} /* namespace Mocxygen */

#endif /* REGISTER_USER_HELPER_H */