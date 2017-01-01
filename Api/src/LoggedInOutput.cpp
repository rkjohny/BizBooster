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


#include "LoggedInOutput.h"
#include "User.h"

namespace Api {

void LoggedInOutput::CopyFrom(LoggedInOutput &&orig)
{
    m_user.copyFrom(std::move(orig.m_user));
}

void LoggedInOutput::CopyFrom(const LoggedInOutput &orig)
{
    m_user.copyFrom(orig.m_user);
}

LoggedInOutput::~LoggedInOutput()
{
}

const Dal::User& LoggedInOutput::GetUser() const
{
    return m_user;
}

void LoggedInOutput::SetUser(const Dal::User &user)
{
    m_user = user;
}

string LoggedInOutput::Name() const
{
    return "LoggedInOutput";
}

string LoggedInOutput::ToString() const
{
    return "LoggedInOutput";
}


}

