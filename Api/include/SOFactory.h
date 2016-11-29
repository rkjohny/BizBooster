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

#include "StringUtility.h"
#include <string>
#include <map>
#include <mutex>
#include <vector>
#include "Serializable.h"
#include <memory>


namespace Api {
    using namespace std;
    using namespace Json;

#define REGISTER_CLASS(TYPE, NAME) \
    Api::SOFactory::Register<TYPE>(NAME);

#define REGISTER_CLASS_DEF(TYPE, KEY, ID) \
    private: static Api::ClassRegistrar<TYPE> _class_registrar_##ID;

#define REGISTER_CLASS_DEC(TYPE, KEY, ID) \
    Api::ClassRegistrar<TYPE> \
        TYPE::_class_registrar_##ID = Json::ClassRegistrar<TYPE>( string(KEY) );

    class SOFactory {
    public:

        static std::unique_ptr<Serializable>CreateObject(string &&key);
        static std::vector<std::unique_ptr<Serializable>> CreateObjectArray(string &&key, const size_t size);

        template< class T >
        static void Register(string &&key) {
            static_assert(std::is_base_of< Serializable, T >::value, "T must be derived from Serializable");
            Common::StringUtility::ToLower(key);

            cm_mutex.lock();
            cm_objectCreators[ key ] = &Create< T >;
            cm_mutex.unlock();

            cm_mutexArr.lock();
            cm_objectArrayCreators[ key ] = &CreateArrary< T >;
            cm_mutexArr.unlock();

            cout << cm_objectCreators.size() << endl;
            cout << cm_objectArrayCreators.size() << endl;
        }

    protected:
        SOFactory() = default;

        typedef std::unique_ptr<Serializable> (*FunPtr)(void);
        typedef map< string, FunPtr > ListCreators;

        typedef std::vector<std::unique_ptr<Serializable>> (*FunPtrArr)(const size_t);
        typedef map< string, FunPtrArr > ListCreatorsArr;

        template< class T >
        static std::unique_ptr<Serializable> Create() {
            return std::make_unique<T>();
        }

        template< class T >
        static std::vector< std::unique_ptr<Serializable>> CreateArrary(const size_t size) {
            std::vector< std::unique_ptr<Serializable>> v;
            for (size_t i = 0; i < size; i++) {
                v.push_back(std::make_unique<T>());
            }
            return v;
        }

        static mutex cm_mutex;
        static ListCreators cm_objectCreators;

        static mutex cm_mutexArr;
        static ListCreatorsArr cm_objectArrayCreators;
    };

    template< class T >
    class ClassRegistrar {
    public:

        ClassRegistrar(string &&key) {
            SOFactory::Register< T >( std::move(key) );
        }

    protected:
        ClassRegistrar() = default;
    };


} /* namespace Api */

#endif /* SOBJECTFACTORY_H_ */

