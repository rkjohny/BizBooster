/**
 * RegisterUserOutput.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "RegisterUserOutput.h"
#include "SObjectFactory.h"

namespace Api {

RegisterUserOutput::RegisterUserOutput() :
        m_age( 0 ), m_price( 0 ), m_isValid( false ), user( nullptr ), users( nullptr ), emails(
                nullptr )
{
    m_className = "RegisterUserOutput";
}

RegisterUserOutput::~RegisterUserOutput()
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

void RegisterUserOutput::RegisterClass()
{
}

string RegisterUserOutput::ClassName() const
{
    return m_className;
}

string* RegisterUserOutput::GetEmail( void )
{
    return &m_email;
}

void RegisterUserOutput::SetEmail( string email )
{
    this->m_email = email;
}

int* RegisterUserOutput::GetAge()
{
    return &m_age;
}

void RegisterUserOutput::SetAge( int val )
{
    m_age = val;
}

double* RegisterUserOutput::GetPrice()
{
    return &m_price;
}

void RegisterUserOutput::SetPrice( double val )
{
    m_price = val;
}

bool* RegisterUserOutput::GetIsValid()
{
    return &m_isValid;
}

void RegisterUserOutput::SetIsValid( bool val )
{
    m_isValid = val;
}

Serializeable** RegisterUserOutput::GetUser()
{
    return reinterpret_cast< Serializeable** >( &user );
}

void RegisterUserOutput::SetUser( Serializeable* val )
{
    user = reinterpret_cast< User* >( val );
}

vector< Serializeable* >** RegisterUserOutput::GetUsers()
{
    return reinterpret_cast< vector< Serializeable* >** >( &users );
}

void RegisterUserOutput::SetUsers( vector< Serializeable * >* val )
{
    users = reinterpret_cast< vector< User * >* >( val );
}

std::vector< std::string >** RegisterUserOutput::GetEmails()
{
    return &emails;
}

void RegisterUserOutput::SetEmails( vector< std::string >* val )
{
    emails = val;
}

} /* namespace Api */
