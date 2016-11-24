/*
 * RegisterClass.h
 *
 *  Created on: Oct 14, 2016
 *      Author: rezaul
 */

#ifndef REGISTERCLASS_H_
#define REGISTERCLASS_H_

#include "SObjectFactory.h"
#include <string>

#include <iostream>

namespace Common {
using namespace std;

#define REGISTER_CLASS(TYPE, NAME) \
		RegisterClass::Register<TYPE>(string(NAME));

class RegisterClass: public SObjectFactory
{
public:

    template< class T >
    static void Register( string &&key )
    {
        static_assert(std::is_base_of< Serializeable, T >::value, "T must be derived from Serializeable");
        StringUtils::ToLower( key );

        cm_mutex.lock();
        cm_objectCreators[ std::move(key) ] = &Create< T >;
        cm_mutex.unlock();

        cm_mutexArr.lock();
        cm_objectArrayCreators[ std::move(key) ] = &CreateArrary< T >;
        cm_mutexArr.unlock();

        cout << cm_objectCreators.size() << endl;
        cout << cm_objectArrayCreators.size() << endl;
    }

protected:
    RegisterClass() = default;
};

template< class T >
class ClassRegistrar: public SObjectFactory
{
public:

    explicit ClassRegistrar( string key )
    {
        RegisterClass::Register< T >( std::move( key ) );
    }

protected:
    ClassRegistrar() = default;
};

} /* namespace Common */

#endif /* REGISTERCLASS_H_ */
