/**
 * SOFactory.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "SOFactory.h"
#include "StringUtils.h"


namespace Json
{
using namespace Common;

mutex SOFactory::cm_mutex;
SOFactory::ListCreators SOFactory::cm_objectCreators;

mutex SOFactory::cm_mutexArr;
SOFactory::ListCreatorsArr SOFactory::cm_objectArrayCreators;

Serializable* SOFactory::CreateObject( string &&key )
{
    Serializable* p = nullptr;
    StringUtils::ToLower( key );

    cm_mutex.lock();
    ListCreators::iterator itr = cm_objectCreators.find( std::move(key) );
    if ( itr != cm_objectCreators.end() )
    {
        p = itr->second();
    }
    cm_mutex.unlock();

    return p;
}

vector< Serializable* >* SOFactory::CreateObjectArray(string &&key, const size_t size )
{
    vector< Serializable* >* v = nullptr;
    StringUtils::ToLower( key );

    cm_mutexArr.lock();
    ListCreatorsArr::iterator itr = cm_objectArrayCreators.find( std::move(key) );
    if ( itr != cm_objectArrayCreators.end() )
    {
        v = itr->second( size );
    }
    cm_mutexArr.unlock();
    return v;
}

} /* namespace Api */
