/**
 * RegisterUserOutput.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef REGISTERUSEROUTPUT_H_
#define REGISTERUSEROUTPUT_H_

#include "BaseOutput.h"
#include "User.h"
#include "Json.h"

#include <vector>

namespace Api
{
using namespace std;
using namespace Common;

class RegisterUserOutput: public BaseOutput
{
public:
    RegisterUserOutput();
    ~RegisterUserOutput();

    void RegisterClass() override;
    string ClassName() const override;

    string* GetEmail( void );
    void SetEmail( string email );

    int* GetAge();
    void SetAge( int val );

    double* GetPrice();
    void SetPrice( double val );

    bool* GetIsValid();
    void SetIsValid( bool val );

    Serializeable** GetUser();
    void SetUser( Serializeable* val );

    vector< Serializeable* >** GetUsers();
    void SetUsers( vector< Serializeable* >* val );

    std::vector< std::string >** GetEmails();
    void SetEmails( std::vector< std::string >* val );

private:
    string m_className;

    string m_email;
    int m_age;
    double m_price;
    bool m_isValid;

    User* user;
    vector< User * >* users;

    vector< string >* emails;

    REGISTER_GETTER_START
    REGISTER_GETTER_END

    REGISTER_SETTER_START
    REGISTER_SETTER_END
};

} /* namespace Api */

#endif /* REGISTERUSEROUTPUT_H_ */
