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

namespace Api {

    //TODO: FOrward declaration
    class RegisterUserInput;

    class RegisterUserHelper : public AbstractHelper {
    private:
        RegisterUserHelper(const RegisterUserHelper& helper) = delete;
        RegisterUserHelper& operator=(const RegisterUserHelper&) = delete;

        RegisterUserInput *m_input;

    public:
        RegisterUserHelper();
        explicit RegisterUserHelper(RegisterUserInput* input);

        void SetInput(RegisterUserInput* in);

        void ValidateInput() override;

        void Initialize() override;

        void CheckPermission() override;

        void ExecuteHelper() override;
    };

} /* namespace Api */

#endif /* REGISTERUSERHELPER_H_ */
