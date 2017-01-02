/**
 * SOFactory.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2016 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "SOFactory.h"

namespace Json {

mutex SOFactory::cm_mutex;
SOFactory::ListCreators SOFactory::cm_objectCreators;

mutex SOFactory::cm_mutexArr;
SOFactory::ListCreatorsArr SOFactory::cm_objectArrayCreators;


std::shared_ptr<Serializable> SOFactory::CreateObject(const string &key)
{
    std::shared_ptr<Serializable> p = nullptr;
    auto lwKey = key;
    Common::StringUtility::ToLower(lwKey);

    cout << cm_objectCreators.size() << endl;
    cout << cm_objectArrayCreators.size() << endl;

    cm_mutex.lock();
    ListCreators::iterator itr = cm_objectCreators.find(lwKey);
    if (itr != cm_objectCreators.end()) {
        p = std::move( itr->second() );
    }
    cm_mutex.unlock();

    return p;
}


std::vector< std::shared_ptr<Serializable>> SOFactory::CreateObjectArray(const string &key, const size_t size)
{
    std::vector< std::shared_ptr<Serializable>> v;
    auto lwKey = key;
    Common::StringUtility::ToLower(lwKey);

    cm_mutexArr.lock();
    ListCreatorsArr::iterator itr = cm_objectArrayCreators.find(lwKey);
    if (itr != cm_objectArrayCreators.end()) {
        v =  std::move( itr->second(size) );
    }
    cm_mutexArr.unlock();
    return v;
}


void SOFactory::Clear()
{
    cm_mutex.lock();
    cm_objectCreators.clear();
    cm_mutex.unlock();
    
    cm_mutexArr.lock();
    cm_objectArrayCreators.clear();
    cm_mutexArr.unlock();
}

} /* namespace Api */
