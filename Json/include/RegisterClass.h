/*
 * RegisterClass.h
 *
 *  Created on: Oct 14, 2016
 *      Author: rezaul
 */

#ifndef REGISTERCLASS_H_
#define REGISTERCLASS_H_

#include "SOFactory.h"
#include "StringUtils.h"
#include <string>

#include <iostream>

namespace Json {
using namespace std;

#define REGISTER_CLASS(TYPE, NAME) \
		RegisterClass::Register<TYPE>(string(NAME));

#define REGISTER_CLASS_DEF(TYPE, KEY) \
        private: static Json::ClassRegistrar<TYPE> _class_registrar_##KEY;

#define REGISTER_CLASS_DEC(TYPE, KEY) \
        Json::ClassRegistrar<TYPE> \
        TYPE::_class_registrar_##KEY = Json::ClassRegistrar<TYPE>( "##KEY" );

class RegisterClass: public SOFactory
{
public:

    template< class T >
    static void Register( string &&key )
    {
        static_assert(std::is_base_of< Serializable, T >::value, "T must be derived from Serializable");
        Common::StringUtils::ToLower( key );

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
class ClassRegistrar: public SOFactory
{
public:

    ClassRegistrar( string &&key )
    {
        RegisterClass::Register< T >( std::move( key ) );
    }

protected:
    ClassRegistrar() = default;
};

} /* namespace Common */

#endif /* REGISTERCLASS_H_ */
