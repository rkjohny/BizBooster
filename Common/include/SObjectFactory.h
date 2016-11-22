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

#include <map>
#include <mutex>
#include <vector>
#include <type_traits>
#include "Serializeable.h"
#include "StringUtils.h"

namespace Common {
using namespace std;

class SObjectFactory
{
public:
    static Serializeable* CreateObject( const string& key );
    static vector< Serializeable* >* CreateObjectArray( const string& key, const size_t size );

protected:
    SObjectFactory() = default;

    typedef Serializeable* (*FunPtr)( void );
    typedef map< string, FunPtr > ListCreators;

    typedef vector< Serializeable* >* (*FunPtrArr)( const size_t );
    typedef map< string, FunPtrArr > ListCreatorsArr;

    template< class T >
    static Serializeable* Create()
    {
        Serializeable* p = reinterpret_cast< Serializeable* >( new T() );
        return p;
    }

    template< class T >
    static vector< Serializeable* >* CreateArrary( const size_t size )
    {
        vector< Serializeable* >* v = new vector< Serializeable * >();
        for (size_t i = 0; i < size; i++)
        {
            Serializeable* p = reinterpret_cast< Serializeable* >( new T() );
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
