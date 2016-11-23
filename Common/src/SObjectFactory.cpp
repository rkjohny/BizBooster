/**
 * SObjectFactory.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "SObjectFactory.h"

namespace Common
{

mutex SObjectFactory::cm_mutex;
SObjectFactory::ListCreators SObjectFactory::cm_objectCreators;

mutex SObjectFactory::cm_mutexArr;
SObjectFactory::ListCreatorsArr SObjectFactory::cm_objectArrayCreators;

Serializeable* SObjectFactory::CreateObject( const string& key )
{
    Serializeable* p = nullptr;
    string lowerKey = key;
    StringUtils::ToLower( lowerKey );

    cm_mutex.lock();
    ListCreators::iterator itr = cm_objectCreators.find( lowerKey );
    if ( itr != cm_objectCreators.end() )
    {
        p = itr->second();
    }
    cm_mutex.unlock();

    return p;
}

vector< Serializeable* >* SObjectFactory::CreateObjectArray( const string& key, const size_t size )
{
    vector< Serializeable* >* v = nullptr;
    string lowerKey = key;
    StringUtils::ToLower( lowerKey );

    cm_mutexArr.lock();
    ListCreatorsArr::iterator itr = cm_objectArrayCreators.find( lowerKey );
    if ( itr != cm_objectArrayCreators.end() )
    {
        v = itr->second( size );
    }
    cm_mutexArr.unlock();
    return v;
}

} /* namespace Api */
