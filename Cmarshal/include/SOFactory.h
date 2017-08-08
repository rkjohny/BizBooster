/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef CMARSHAL_JSON_SO_FACTOTY_H
#define CMARSHAL_JSON_SO_FACTOTY_H

#include "StringUtils.h"
#include <string>
#include <map>
#include <vector>
#include "AbstractSerializable.h"
#include <memory>
#include "boost/thread.hpp"


namespace  Cmarshal {
    namespace Json {
        using namespace std;

#define REGISTER_CLASS(TYPE, NAME) \
    Cmarshal::Json::SOFactory::Register<TYPE>(NAME);

#define REGISTER_CLASS_DEF(TYPE, KEY, ID) \
    private: static Cmarshal::Json::ClassRegistrar<TYPE> _class_registrar_##ID;

#define REGISTER_CLASS_DEC(TYPE, KEY, ID) \
    Cmarshal::Json::ClassRegistrar<TYPE> \
        TYPE::_class_registrar_##ID = Json::ClassRegistrar<TYPE>( string(KEY) );


#define UNREGISTER_CLASS(TYPE, NAME) \
    Cmarshal::Json::SOFactory::UnRegister<TYPE>(NAME);

        class SOFactory {
        public:

            static std::shared_ptr<AbstractSerializable> CreateObject(const string &key);

            static std::vector<std::shared_ptr<AbstractSerializable>> CreateObjectArray(const string &key, const size_t size);

            template<class T>
            static void Register(const string &key) {
                static_assert(std::is_base_of<AbstractSerializable, T>::value, "T must be derived from AbstractSerializable");
                std::string lwKey = key;
                Common::StringUtils::ToLower(lwKey);

                cm_mutex.lock();
                cm_objectCreators[lwKey] = &Create<T>;
                cm_mutex.unlock();

                cm_mutexArr.lock();
                cm_objectArrayCreators[lwKey] = &CreateArrary<T>;
                cm_mutexArr.unlock();

                cout << cm_objectCreators.size() << endl;
                cout << cm_objectArrayCreators.size() << endl;
            }

            template<class T>
            static void UnRegister(const string &key) {
                static_assert(std::is_base_of<AbstractSerializable, T>::value, "T must be derived from AbstractSerializable");
                std::string lwKey = key;
                Common::StringUtils::ToLower(lwKey);

                cm_mutex.lock();
                auto itrObj = cm_objectCreators.find(lwKey);
                if (itrObj != cm_objectCreators.end()) {
                    cm_objectCreators.erase(itrObj);
                }
                cm_mutex.unlock();


                cm_mutexArr.lock();
                auto itrArr = cm_objectArrayCreators.find(lwKey);
                if (itrArr != cm_objectArrayCreators.end()) {
                    cm_objectArrayCreators.erase(itrArr);
                }
                cm_mutexArr.unlock();
            }

            static void Clear();

        protected:
            SOFactory() = default;

            typedef std::shared_ptr<AbstractSerializable> (*FunPtr)(void);

            typedef map<string, FunPtr> ListCreators;

            typedef std::vector<std::shared_ptr<AbstractSerializable>> (*FunPtrArr)(const size_t);

            typedef map<string, FunPtrArr> ListCreatorsArr;

            template<class T>
            static std::shared_ptr<AbstractSerializable> Create() {
                return std::make_shared<T>();
            }

            template<class T>
            static std::vector<std::shared_ptr<AbstractSerializable>> CreateArrary(const size_t size) {
                std::vector<std::shared_ptr<AbstractSerializable>> v;
                for (size_t i = 0; i < size; i++) {
                    v.push_back(std::make_shared<T>());
                }
                return v;
            }

            static boost::mutex cm_mutex;
            static ListCreators cm_objectCreators;

            static boost::mutex cm_mutexArr;
            static ListCreatorsArr cm_objectArrayCreators;
        };

        template<class T>
        class ClassRegistrar {
        public:

            ClassRegistrar(const string &key) {
                SOFactory::Register<T>(key);
            }

        protected:
            ClassRegistrar() = default;
        };


    } /* namespace Json */
} /* namespace Cmarshal */

#endif /* CMARSHAL_JSON_SO_FACTOTY_H */

