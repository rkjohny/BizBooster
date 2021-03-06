/**
 * SOFactory.cpp
 *
 *      Author: rezaul
 *
 * Copyright (C) 2017 Rezaul Karim, rkjohny@gmail.com. All rights reserved.
 * Nobody should use this file without taking written permission from the author.
 */

#include "SOFactory.h"

namespace Cmarshal {
    namespace Json {

        boost::mutex SOFactory::cm_mutex;
        SOFactory::ListCreators SOFactory::cm_objectCreators;

        boost::mutex SOFactory::cm_mutexArr;
        SOFactory::ListCreatorsArr SOFactory::cm_objectArrayCreators;


        std::shared_ptr<AbstractSerializable> SOFactory::CreateObject(const std::string &key) {
            std::shared_ptr<AbstractSerializable> p = nullptr;
            std::string lwKey = key;
            Common::StringUtils::ToLower(lwKey);
            
            cm_mutex.lock();
            ListCreators::iterator itr = cm_objectCreators.find(lwKey);
            if (itr != cm_objectCreators.end()) {
                p = std::move(itr->second());
            }
            cm_mutex.unlock();

            return p;
        }


        std::vector<std::shared_ptr<AbstractSerializable>> SOFactory::CreateObjectArray(const std::string &key, const size_t size) {
            std::vector<std::shared_ptr<AbstractSerializable>> v;
            std::string lwKey = key;
            Common::StringUtils::ToLower(lwKey);

            cm_mutexArr.lock();
            ListCreatorsArr::iterator itr = cm_objectArrayCreators.find(lwKey);
            if (itr != cm_objectArrayCreators.end()) {
                v = std::move(itr->second(size));
            }
            cm_mutexArr.unlock();
            return v;
        }


        void SOFactory::Clear() {
            cm_mutex.lock();
            cm_objectCreators.clear();
            cm_mutex.unlock();

            cm_mutexArr.lock();
            cm_objectArrayCreators.clear();
            cm_mutexArr.unlock();
        }

    } /* namespace Json */
} /* namespace Cmarshal */