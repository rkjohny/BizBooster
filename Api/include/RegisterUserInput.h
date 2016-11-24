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
// and do not forward declare Serializeable class it is base class

#include <string>
#include <vector>
#include "BaseInput.h"
#include "SObjectFactory.h"
#include "User.h"
#include "Json.h"

namespace Api
{
using namespace std;
using namespace Common;

class RegisterUserInput: public BaseInput
{
public:
    RegisterUserInput();
    ~RegisterUserInput();

    void RegisterClass() override;
    string ClassName() const override;
    string ApiName() const override;
    BaseOutput* Process() override;

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
    string m_apiName;

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

#endif /* REGISTERUSERINPUT_H_ */
