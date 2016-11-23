/**
 * User.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#include "User.h"
#include "RegisterClass.h"

namespace Api
{

User::User() :
    name( "" ), id( 0 )
{
}

User::~User()
{
}

string User::ClassName() const
{
    return "User";
}

void User::RegisterClass()
{
    REGISTER_CLASS( User, ClassName() );
}

string* User::GetName()
{
    return &name;
}

void User::SetName( string val )
{
    name = val;
}

int* User::GetId()
{
    return &id;
}

void User::SetId( int val )
{
    id = val;
}

}
