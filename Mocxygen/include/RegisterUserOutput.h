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

#include "BaseOutput.h"
#include "User.h"


namespace Mocxygen {
    using namespace std;
    using namespace Cmarshal::Json;
    using namespace Cruxdb;

    class RegisterUserOutput : public ApiOutput<RegisterUserOutput> {
    public:
        API_OUTPUT(RegisterUserOutput);
        
        ~RegisterUserOutput() = default;

        Wt::Dbo::ptr<User> GetUser() const;
        void SetUser(Wt::Dbo::ptr<User> &user);

        REGISTER_GETTER_INCLUDING_BASE_START(ApiOutput<RegisterUserOutput>)
        GETTER(RegisterUserOutput, Wt::Dbo::ptr<User>, "user", &RegisterUserOutput::GetUser)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(ApiOutput<RegisterUserOutput>)
        SETTER(RegisterUserOutput, Wt::Dbo::ptr<User>&, "user", &RegisterUserOutput::SetUser)
        REGISTER_SETTER_INCLUDING_BASE_END

    private:
        Wt::Dbo::ptr<User> m_user;
    };

} /* namespace Mocxygen */

#endif /* REGISTER_USER_OUTPUT_H */
