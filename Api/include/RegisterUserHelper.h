/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */



#ifndef REGISTER_USER_HELPER_H
#define REGISTER_USER_HELPER_H

#include "AbstractHelper.h"
#include "RegisterUserInput.h"
#include "RegisterUserOutput.h"

namespace Api {

    //TODO: Use forrward declaration of class RegisterUserInput if needed.

    class RegisterUserHelper : public AbstractHelper {
    private:
        NON_COPY_NON_ASSIGN_ABLE(RegisterUserHelper);

    public:
        RegisterUserHelper();
        RegisterUserHelper(RegisterUserInput *input);

        void SetInput(RegisterUserInput *in);

        RegisterUserHelper(RegisterUserInput &input);

        void SetInput(RegisterUserInput &in);

        void ValidateInput() override;

        void Initialize() override;

        void CheckPermission() override;

        void ExecuteHelper() override;
    };

} /* namespace Api */

#endif /* REGISTER_USER_HELPER_H */
