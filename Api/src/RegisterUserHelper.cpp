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

#include "Dao.h"
#include "Dal.h"
#include "RegisterUserHelper.h"
#include "LogFactory.h"

namespace Api {

RegisterUserHelper::RegisterUserHelper()
{
}

RegisterUserHelper::RegisterUserHelper(RegisterUserInput *input)
{
    this->m_input = input;
}

void RegisterUserHelper::SetInput(RegisterUserInput *input)
{
    this->m_input = input;
}

RegisterUserHelper::RegisterUserHelper(RegisterUserInput &input)
{
    this->m_input = &input;
}

void RegisterUserHelper::SetInput(RegisterUserInput &input)
{
    this->m_input = &input;
}

void RegisterUserHelper::InitAndValidate()
{
    RegisterUserInput *input = dynamic_cast<RegisterUserInput*>(m_input);
    User loggedUser = User();
    Wt::Dbo::ptr<Dal::User> user = Dal::GetDao()->GetUser(loggedUser, input->GetEmail());
    
    if (user) {
        throw Common::AppException(AppErrorCode::DUPLICATE_USER, 
                           "User with the email already exists");
    }
}

void RegisterUserHelper::CheckPermission()
{
}

void RegisterUserHelper::ExecuteHelper()
{
    LOG_DEBUG("Api input: " + m_input->Serialize().serialize());

    RegisterUserInput *input = dynamic_cast<RegisterUserInput*>(m_input);

    if (input) {
        User *user = new User();
        user->SetEmail(input->GetEmail());
        user->SetName(input->GetName());
        user->SetRoles(input->GetRoles());
        user->SetVersion(input->GetVersion());
        user->SetPassword(input->GetPassword());
        //TODO: loginname is hardcoded
        user->AddIdentity("loginname", input->GetEmail());

        LOG_DEBUG("Registering new user.");

        User loggedUser = User();
        Wt::Dbo::ptr<User> userAdded = Dal::GetDao()->RegisterUser(loggedUser, user);

        if (userAdded) {
            LOG_DEBUG("New user registered successfully");

            std::unique_ptr<RegisterUserOutput> output = std::make_unique<RegisterUserOutput>();
            output->SetUser(*userAdded);

            m_output = std::move(output);

            LOG_DEBUG("Api output: " + m_output->Serialize().serialize());

        } else {
            throw Common::AppException(AppErrorCode::DB_OPERATION_FAILED,
                    "Database operation of adding new user failed");
        }
    } else {
        throw Common::AppException(AppErrorCode::INTERNAL_SERVER_ERROR,
                "Could not cast pointer of BaseInput to RegisterUserInput");
    }
}

} /* namespace Api */
