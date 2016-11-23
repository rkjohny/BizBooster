/**
 * ApiError.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef APIERROR_H_
#define APIERROR_H_

#include <string>
#include "AppConstant.h"

namespace Api
{
using namespace std;

class ApiError
{
public:
    ApiError();

    void SetCode( const ApiReturnCode& code );
    void SetMessage( const string& message );
    ApiReturnCode GetCode() const;
    string GetMessage() const;

private:
    ApiReturnCode m_code;
    string m_message;
};

} /* namespace Api */

#endif /* APIERROR_H_ */
