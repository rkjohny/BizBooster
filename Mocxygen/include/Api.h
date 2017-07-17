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

#ifndef _SERVICE_FACADE_H_
#define _SERVICE_FACADE_H_

#include "SaveUserOutput.h"
#include "SaveUserInput.h"
#include "LogInOutput.h"
#include "LogInInput.h"
#include "LoggedInInput.h"
#include "LoggedInOutput.h"

namespace Mocxygen {

//TODO: Use forward declaration for class SaveUserInput if needed

class Api {
public:
    static std::shared_ptr<SaveUserOutput> SaveUser(Cruxdb::Requester *requester, SaveUserInput *input,
                                                    SaveUserOutput *output = nullptr);
    
    static std::shared_ptr<LogInOutput> LogIn(Cruxdb::Requester *requester, LogInInput *input, LogInOutput *output = nullptr);

    static std::shared_ptr<LoggedInOutput> UserLoggedIn(Cruxdb::Requester *requester, LoggedInInput *input, LoggedInOutput *output = nullptr);

private:
    MAKE_STATIC(Api);
};

} /* namespace Mocxygen */

#endif /* SERVICEFACADE_H_ */
