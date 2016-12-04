/**
 * RegisterUserOutput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef REGISTERUSEROUTPUT_H_
#define REGISTERUSEROUTPUT_H_

#include "BaseOutput.h"
#include "User.h"


namespace Api {
    using namespace std;
    using namespace Json;
    using namespace Dal;

    class RegisterUserOutput : public ApiOutput<RegisterUserOutput> {
    public:
        RegisterUserOutput();
        ~RegisterUserOutput();

        const User& GetUser() const;
        void SetUser(const User& user);

    private:
        User m_user;

        REGISTER_GETTER_INCLUDING_BASE_START(ApiOutput<RegisterUserOutput>)
        GETTER(RegisterUserOutput, const User&, "user", &RegisterUserOutput::GetUser)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(ApiOutput<RegisterUserOutput>)
        SETTER(RegisterUserOutput, const User&, "user", &RegisterUserOutput::SetUser)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

} /* namespace Api */

#endif /* REGISTERUSEROUTPUT_H_ */
