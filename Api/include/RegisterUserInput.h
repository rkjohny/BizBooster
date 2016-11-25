/**
 * RegisterUserInput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef REGISTERUSERINPUT_H_
#define REGISTERUSERINPUT_H_

//Note: do not include BaseOutpu.h it has been forward declared in BaseInput
// and do not forward declare Serializable class it is base class

#include <string>
#include "RegisterClass.h"
#include "BaseInput.h"
#include "Json.h"

namespace Api
{
using namespace std;
using namespace Json;

class RegisterUserInput: public ApiInput<RegisterUserInput>
{
public:
    RegisterUserInput();
    ~RegisterUserInput();

    BaseOutput* Process() override;

    const std::string& GetEmail() const;
    void SetEmail(std::string email);

    const std::string& GetName() const;
    void SetName(std::string name);

    const std::string& GetRoles() const;
    void SetRoles(std::string roles);

private:
    std::string m_email;
    std::string m_name;
    std::string m_roles;

    REGISTER_ALL_GETTER_START
    BASE_GETTER(ApiInput<RegisterUserInput>)
    OWN_GETTER_START
    GETTER(RegisterUserInput, const std::string&, "email", &RegisterUserInput::GetEmail),
    GETTER(RegisterUserInput, const std::string&, "email", &RegisterUserInput::GetName),
    GETTER(RegisterUserInput, const std::string&, "email", &RegisterUserInput::GetRoles)
    OWN_GETTER_END
    REGISTER_ALL_GETTER_END

    REGISTER_ALL_SETTER_START
    BASE_SETTER(ApiInput<RegisterUserInput>)
    OWN_SETTER_START
    SETTER(RegisterUserInput, std::string, "email", &RegisterUserInput::SetEmail),
    SETTER(RegisterUserInput, std::string, "email", &RegisterUserInput::SetName),
    SETTER(RegisterUserInput, std::string, "email", &RegisterUserInput::SetRoles)
    OWN_SETTER_END
    REGISTER_ALL_SETTER_END

    REGISTER_CLASS_DEF(RegisterUserInput, register_user)
    REGISTER_CLASS_DEF(RegisterUserInput, RegisterUserInput)
};

} /* namespace Api */

#endif /* REGISTERUSERINPUT_H_ */
