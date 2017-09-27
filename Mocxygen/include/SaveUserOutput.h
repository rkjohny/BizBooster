/**
 * RegisterUserOutput.h
 *
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

#ifndef REGISTER_USER_OUTPUT_H
#define REGISTER_USER_OUTPUT_H

#include "AbstractBaseOutput.h"
#include "User.h"
#include <memory>


namespace Mocxygen {
    class SaveUserOutput : public AbstractApiSaveEntityOutput<SaveUserOutput, Cruxdb::User> {
    private:
        using SaveUserOutputT = AbstractApiSaveEntityOutput<SaveUserOutput, Cruxdb::User>;
    public:
        API_OUTPUT(SaveUserOutput);
        
        ~SaveUserOutput() = default;

        REGISTER_GETTER_INCLUDING_BASE_START(SaveUserOutputT)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(SaveUserOutputT)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

} /* namespace Mocxygen */

#endif /* REGISTER_USER_OUTPUT_H */
