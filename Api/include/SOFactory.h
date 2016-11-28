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

#include "StringUtils.h"
#include <string>
#include <map>
#include <mutex>
#include <vector>
#include "Serializable.h"


namespace Api {
    using namespace std;
    using namespace Json;

#define REGISTER_CLASS(TYPE, NAME) \
SOFactory::Register<TYPE>(string(NAME));

#define REGISTER_CLASS_DEF(TYPE, KEY, ID) \
private: static Json::ClassRegistrar<TYPE> _class_registrar_##ID;

#define REGISTER_CLASS_DEC(TYPE, KEY, ID) \
Json::ClassRegistrar<TYPE> \
TYPE::_class_registrar_##ID = Json::ClassRegistrar<TYPE>( string(KEY) );

    class SOFactory {
    public:

        static void Load();

        static Serializable* CreateObject(string &&key);
        static vector< Serializable* >* CreateObjectArray(string &&key, const size_t size);

        template< class T >
        static void Register(string key) {
            static_assert(std::is_base_of< Serializable, T >::value, "T must be derived from Serializable");
            Common::StringUtils::ToLower(key);

            cm_mutex.lock();
            cm_objectCreators[ key ] = &Create< T >;
            //cm_objectCreators.insert(std::pair<string, FunPtr>(key, &Create< T >));
            cm_mutex.unlock();

            cm_mutexArr.lock();
            cm_objectArrayCreators[ key ] = &CreateArrary< T >;
            cm_mutexArr.unlock();

            cout << cm_objectCreators.size() << endl;
            cout << cm_objectArrayCreators.size() << endl;
        }

    protected:
        SOFactory() = default;

        typedef Serializable* (*FunPtr)(void);
        typedef map< string, FunPtr > ListCreators;

        typedef vector< Serializable* >* (*FunPtrArr)(const size_t);
        typedef map< string, FunPtrArr > ListCreatorsArr;

        template< class T >
        static Serializable* Create() {
            Serializable* p = reinterpret_cast<Serializable*> (new T());
            return p;
        }

        template< class T >
        static vector< Serializable* >* CreateArrary(const size_t size) {
            vector< Serializable* >* v = new vector< Serializable * >();
            for (size_t i = 0; i < size; i++) {
                Serializable* p = reinterpret_cast<Serializable*> (new T());
                v->push_back(p);
            }
            return v;
        }

        static mutex cm_mutex;
        static ListCreators cm_objectCreators;

        static mutex cm_mutexArr;
        static ListCreatorsArr cm_objectArrayCreators;
    };

    template< class T >
    class ClassRegistrar : public SOFactory {
    public:

        ClassRegistrar(string key) {
            SOFactory::Register< T >(key);
        }

    protected:
        ClassRegistrar() = default;
    };


} /* namespace Api */

#endif /* SOBJECTFACTORY_H_ */

