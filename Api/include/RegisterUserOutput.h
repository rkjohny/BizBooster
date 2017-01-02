/**
 * RegisterUserOutput.h
 *
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

#ifndef REGISTER_USER_OUTPUT_H
#define REGISTER_USER_OUTPUT_H

#include "BaseOutput.h"
#include "User.h"


namespace Api {
    using namespace std;
    using namespace Json;
    using namespace Dal;

    class RegisterUserOutput : public ApiOutput<RegisterUserOutput> {
    public:
        API_OUTPUT(RegisterUserOutput);
        
        ~RegisterUserOutput() = default;

        Wt::Dbo::ptr<User> GetUser() const;
        void SetUser(Wt::Dbo::ptr<User> &user);

    private:
        Wt::Dbo::ptr<User> m_user;

        REGISTER_GETTER_INCLUDING_BASE_START(ApiOutput<RegisterUserOutput>)
        GETTER(RegisterUserOutput, Wt::Dbo::ptr<User>, "user", &RegisterUserOutput::GetUser)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(ApiOutput<RegisterUserOutput>)
        SETTER(RegisterUserOutput, Wt::Dbo::ptr<User>&, "user", &RegisterUserOutput::SetUser)
        REGISTER_SETTER_INCLUDING_BASE_END
    };

} /* namespace Api */

#endif /* REGISTER_USER_OUTPUT_H */
