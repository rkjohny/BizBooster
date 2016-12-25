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

#include "LogInOutput.h"
#include "User.h"

namespace Api {

LogInOutput::LogInOutput()
{
}

LogInOutput::LogInOutput(const LogInOutput& orig)
{
    m_user.copyFrom(orig.m_user);
}

LogInOutput::LogInOutput(LogInOutput&& orig)
{
    m_user.copyFrom(std::move(orig.m_user));
}

LogInOutput::~LogInOutput()
{
}

const Dal::User& LogInOutput::GetUser() const
{
    return m_user;
}

void LogInOutput::SetUser(const Dal::User &user)
{
    m_user.copyFrom(user);
}

}