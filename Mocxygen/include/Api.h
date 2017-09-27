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
#include "LoginOutput.h"
#include "LoginInput.h"
#include "LoggedinInput.h"
#include "LoggedinOutput.h"

namespace Mocxygen {
    class Api {
    private:
        MAKE_STATIC(Api);

    public:
        static std::shared_ptr<SaveUserOutput> SaveUser(std::shared_ptr<Cruxdb::Requester> requester,
                                                        std::shared_ptr<SaveUserInput> input,
                                                        std::shared_ptr<SaveUserOutput> output = nullptr);

        static std::shared_ptr<LoginOutput> LogIn(std::shared_ptr<Cruxdb::Requester> requester,
                                                  std::shared_ptr<LoginInput> input,
                                                  std::shared_ptr<LoginOutput> output = nullptr);

        static std::shared_ptr<LoggedinOutput> UserLoggedIn(std::shared_ptr<Cruxdb::Requester> requester,
                                                            std::shared_ptr<LoggedinInput> input,
                                                            std::shared_ptr<LoggedinOutput> output = nullptr);
    };

} /* namespace Mocxygen */

#endif /* SERVICEFACADE_H_ */
