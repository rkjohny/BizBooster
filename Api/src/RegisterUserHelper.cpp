/**
 * RegisterUserHelper.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include <Dao.h>
#include "Dal.h"
#include "RegisterUserHelper.h"
#include "AppFactory.h"

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

void RegisterUserHelper::ValidateInput()
{
}

void RegisterUserHelper::Initialize()
{
}

void RegisterUserHelper::CheckPermission()
{
}

void RegisterUserHelper::ExecuteHelper()
{
    LOG_DEBUG("Api input: " + m_input->Serialize().serialize());

    User *user = new User();
    user->SetEmail(m_input->GetEmail());
    user->SetName(m_input->GetName());
    user->SetRoles(m_input->GetRoles());
    user->SetVersion(m_input->GetVersion());
    user->SetPassword(m_input->GetPassword());

    User loggedUser = User();
    Wt::Dbo::ptr<User> userAdded = Dal::GetDao()->RegisterUser(loggedUser, user);

    std::unique_ptr<RegisterUserOutput> output = std::make_unique<RegisterUserOutput>();
    output->SetUser(*userAdded);

    m_output = std::move(output);

    LOG_DEBUG("Api output: " + m_output->Serialize().serialize());
}

} /* namespace Api */
