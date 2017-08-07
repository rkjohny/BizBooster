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

#include "AbstractApiHelper.h"
#include "SaveUserInput.h"
#include "SaveUserOutput.h"

namespace Mocxygen {


class SaveUserHelper : public AbstractApiHelper <SaveUserInput, SaveUserOutput> {
private:
    API_HELPER(SaveUserHelper);
    
    Wt::Dbo::ptr<Cruxdb::User> m_user;

public:
    ~SaveUserHelper() = default;

    SaveUserHelper(Cruxdb::Requester *requester, SaveUserInput *input, SaveUserOutput *output = nullptr) :
    AbstractApiHelper<SaveUserInput, SaveUserOutput>(requester, input, output)
    {
    }

    void ExecuteHelper() noexcept(false) override;
};

} /* namespace Mocxygen */

#endif /* REGISTER_USER_HELPER_H */
