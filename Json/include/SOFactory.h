/**
 * SObjectFactory.h
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#ifndef SOBJECTFACTORY_H_
#define SOBJECTFACTORY_H_


#include <string>
#include <map>
#include <mutex>
#include <vector>
//#include <type_traits>
#include "Serializable.h"


namespace Json {
using namespace std;
using namespace Json;

class SOFactory
{
public:
    static Serializable* CreateObject( string key );
    static vector< Serializable* >* CreateObjectArray( string key, const size_t size );

protected:
    SOFactory() = default;

    typedef Serializable* (*FunPtr)( void );
    typedef map< string, FunPtr > ListCreators;

    typedef vector< Serializable* >* (*FunPtrArr)( const size_t );
    typedef map< string, FunPtrArr > ListCreatorsArr;

    template< class T >
    static Serializable* Create()
    {
        Serializable* p = reinterpret_cast< Serializable* >( new T() );
        return p;
    }

    template< class T >
    static vector< Serializable* >* CreateArrary( const size_t size )
    {
        vector< Serializable* >* v = new vector< Serializable * >();
        for (size_t i = 0; i < size; i++)
        {
            Serializable* p = reinterpret_cast< Serializable* >( new T() );
            v->push_back( p );
        }
        return v;
    }

    static mutex cm_mutex;
    static ListCreators cm_objectCreators;

    static mutex cm_mutexArr;
    static ListCreatorsArr cm_objectArrayCreators;
};

} /* namespace Api */

#endif /* SOBJECTFACTORY_H_ */
