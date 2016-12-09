/**
 * RegisterUserHelper.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef REGISTERUSERHELPER_H_
#define REGISTERUSERHELPER_H_

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

#endif /* REGISTERUSERHELPER_H_ */
