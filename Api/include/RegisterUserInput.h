/**
 * RegisterUserInput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef REGISTERUSERINPUT_H_
#define REGISTERUSERINPUT_H_

#include <string>
#include "SOFactory.h"
#include "BaseInput.h"
#include "Json.h"

namespace Api {
    using namespace std;
    using namespace Json;

    class RegisterUserInput : public ApiInput<RegisterUserInput> {
    public:
        RegisterUserInput();
        ~RegisterUserInput();

        web::json::value Process() override;

        string ToString() override ;

        const std::string& GetEmail() const;
        void SetEmail(std::string email);

        const std::string& GetName() const;
        void SetName(std::string name);

        const std::string& GetRoles() const;
        void SetRoles(std::string roles);

        int GetVersion() const;
        void SetVersion(int version);

        const std::string& GetPassword() const;
        void SetPassword(std::string password);

    private:
        std::string m_email;
        std::string m_name;
        std::string m_roles;
        std::string m_password;
        int m_version;


        REGISTER_GETTER_INCLUDING_BASE_START(ApiInput<RegisterUserInput>)
        GETTER(RegisterUserInput, const std::string&, "email", &RegisterUserInput::GetEmail),
        GETTER(RegisterUserInput, const std::string&, "name", &RegisterUserInput::GetName),
        GETTER(RegisterUserInput, const std::string&, "roles", &RegisterUserInput::GetRoles),
        GETTER(RegisterUserInput, const std::string&, "password", &RegisterUserInput::GetPassword),
        GETTER(RegisterUserInput, int, "version", &RegisterUserInput::GetVersion)
        REGISTER_GETTER_INCLUDING_BASE_END

        REGISTER_SETTER_INCLUDING_BASE_START(ApiInput<RegisterUserInput>)
        SETTER(RegisterUserInput, std::string, "email", &RegisterUserInput::SetEmail),
        SETTER(RegisterUserInput, std::string, "name", &RegisterUserInput::SetName),
        SETTER(RegisterUserInput, std::string, "roles", &RegisterUserInput::SetRoles),
        SETTER(RegisterUserInput, std::string, "password", &RegisterUserInput::SetPassword),
        SETTER(RegisterUserInput, int, "version", &RegisterUserInput::SetVersion)
        REGISTER_SETTER_INCLUDING_BASE_END

        //REGISTER_CLASS_DEF(RegisterUserInput, "register_user", 0)
        //REGISTER_CLASS_DEF(RegisterUserInput, "RegisterUserInput", 1)
    };

} /* namespace Api */

#endif /* REGISTERUSERINPUT_H_ */
