/**
 * RegisterUserInput.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "RegisterUserInput.h"
#include "ServiceFacade.h"
#include "RegisterClass.h"


#define REGISTER_USER_API_NAME "register_user"

namespace Api {

RegisterUserInput::RegisterUserInput() :
        m_age( 0 ), m_price( 0 ), m_isValid( false ), user( nullptr ), users( nullptr ), emails(
                nullptr )
{
    m_className = "RegisterUserInput";
    m_apiName = REGISTER_USER_API_NAME;
}

RegisterUserInput::~RegisterUserInput()
{
    if ( user )
    {
        delete user;
    }
    if ( users )
    {
        delete[] users;
    }
    if ( emails )
    {
        delete emails;
    }
}

void RegisterUserInput::RegisterClass()
{
    REGISTER_CLASS( RegisterUserInput, ApiName() );
    REGISTER_CLASS( RegisterUserInput, ClassName() );
}

string RegisterUserInput::ClassName() const
{
    return m_className;
}

string RegisterUserInput::ApiName() const
{
    return m_apiName;
}

BaseOutput* RegisterUserInput::Process()
{
    return ServiceFacade::RegisterUser( this );
}

string* RegisterUserInput::GetEmail( void )
{
    return &m_email;
}

void RegisterUserInput::SetEmail( string email )
{
    this->m_email = email;
}

int* RegisterUserInput::GetAge()
{
    return &m_age;
}

void RegisterUserInput::SetAge( int val )
{
    m_age = val;
}

double* RegisterUserInput::GetPrice()
{
    return &m_price;
}

void RegisterUserInput::SetPrice( double val )
{
    m_price = val;
}

bool* RegisterUserInput::GetIsValid()
{
    return &m_isValid;
}

void RegisterUserInput::SetIsValid( bool val )
{
    m_isValid = val;
}

Serializeable** RegisterUserInput::GetUser()
{
    return reinterpret_cast< Serializeable** >( &user );
}

void RegisterUserInput::SetUser( Serializeable* val )
{
    user = reinterpret_cast< User* >( val );
}

vector< Serializeable* >** RegisterUserInput::GetUsers()
{
    return reinterpret_cast< vector< Serializeable* >** >( &users );
}

void RegisterUserInput::SetUsers( vector< Serializeable * >* val )
{
    users = reinterpret_cast< vector< User * >* >( val );
}

std::vector< std::string >** RegisterUserInput::GetEmails()
{
    return &emails;
}

void RegisterUserInput::SetEmails( vector< std::string >* val )
{
    emails = val;
}

} /* namespace Api */

