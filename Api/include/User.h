/**
 * User.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 */

#ifndef USER_H_
#define USER_H_

#include <string>
#include "Serializeable.h"

namespace Api
{
using namespace std;
using namespace Common;

class User: public Serializeable
{
public:
    User();
    ~User();

    string* GetName();
    void SetName( string val );
    int* GetId();
    void SetId( int val );

    void RegisterClass() override;
    string ClassName() const override;

private:
    string name;
    int id;
};

} /* namespace Api */

#endif /* USER_H_ */
