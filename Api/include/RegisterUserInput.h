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

#ifndef REGISTER_USER_INPUT_H
#define REGISTER_USER_INPUT_H

#include <string>
#include "BaseInput.h"
#include "Json.h"
#include "AppDef.h"

namespace Api {
using namespace std;
using namespace Json;

class RegisterUserInput : public ApiInput<RegisterUserInput> {
public:
    SERIALIZEABLE(RegisterUserInput);
    ~RegisterUserInput() = default;
    
    web::json::value Process() override;
    
    const std::string& GetEmail() const;
    void SetEmail(const std::string &email);

    const std::string& GetName() const;
    void SetName(const std::string &name);

    const std::string& GetRoles() const;
    void SetRoles(const std::string &roles);

    int GetVersion() const;
    void SetVersion(const int &version);

    const std::string& GetPassword() const;
    void SetPassword(const std::string &password);
    
    const std::string& GetStatus() const;
    void SetStatus(const std::string &status);

private:
    std::string m_email;
    std::string m_name;
    std::string m_roles;
    std::string m_password;
    int m_version;
    std::string m_status;


    REGISTER_GETTER_INCLUDING_BASE_START(ApiInput<RegisterUserInput>)
    GETTER(RegisterUserInput, const std::string&, "email", &RegisterUserInput::GetEmail),
    GETTER(RegisterUserInput, const std::string&, "name", &RegisterUserInput::GetName),
    GETTER(RegisterUserInput, const std::string&, "roles", &RegisterUserInput::GetRoles),
    GETTER(RegisterUserInput, const std::string&, "password", &RegisterUserInput::GetPassword),
    GETTER(RegisterUserInput, const std::string&, "status", &RegisterUserInput::GetStatus),
    GETTER(RegisterUserInput, int, "version", &RegisterUserInput::GetVersion)
    REGISTER_GETTER_INCLUDING_BASE_END

    REGISTER_SETTER_INCLUDING_BASE_START(ApiInput<RegisterUserInput>)
    SETTER(RegisterUserInput, const std::string&, "email", &RegisterUserInput::SetEmail),
    SETTER(RegisterUserInput, const std::string&, "name", &RegisterUserInput::SetName),
    SETTER(RegisterUserInput, const std::string&, "roles", &RegisterUserInput::SetRoles),
    SETTER(RegisterUserInput, const std::string&, "password", &RegisterUserInput::SetPassword),
    SETTER(RegisterUserInput, const std::string&, "status", &RegisterUserInput::SetStatus),
    SETTER(RegisterUserInput, const int&, "version", &RegisterUserInput::SetVersion)
    REGISTER_SETTER_INCLUDING_BASE_END

    //REGISTER_CLASS_DEF(RegisterUserInput, "register_user", 0)
    //REGISTER_CLASS_DEF(RegisterUserInput, "RegisterUserInput", 1)
};

} /* namespace Api */

#endif /* REGISTER_USER_INPUT_H */
