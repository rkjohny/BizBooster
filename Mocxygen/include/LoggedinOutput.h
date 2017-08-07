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


#ifndef LOGGED_IN_OUTPUT_H
#define LOGGED_IN_OUTPUT_H

#include "AbstractBaseOutput.h"
#include "AppCommonDef.h"
#include "User.h"

namespace Mocxygen {
    class LoggedinOutput : public Mocxygen::AbstractApiGetEntityOutput<LoggedinOutput, Cruxdb::User> {
    private:
        using LoggedInOutputT = Mocxygen::AbstractApiGetEntityOutput<LoggedinOutput, Cruxdb::User>;

    public:
        API_OUTPUT(LoggedinOutput);

        virtual ~LoggedinOutput();


        REGISTER_GETTER_INCLUDING_BASE_START(LoggedInOutputT)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(LoggedInOutputT)
        REGISTER_SETTER_INCLUDING_BASE_END

    };
}

#endif /* LOGGEDIN_OUTPUT_H */

