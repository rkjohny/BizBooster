/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#ifndef TINY_JSON_SO_FACTOTY_H
#define TINY_JSON_SO_FACTOTY_H

#include "StringUtility.h"
#include <string>
#include <map>
#include <mutex>
#include <vector>
#include "Serializable.h"
#include <memory>


namespace Json {
    using namespace std;

#define REGISTER_CLASS(TYPE, NAME) \
    Json::SOFactory::Register<TYPE>(NAME);

#define REGISTER_CLASS_DEF(TYPE, KEY, ID) \
    private: static Json::ClassRegistrar<TYPE> _class_registrar_##ID;

#define REGISTER_CLASS_DEC(TYPE, KEY, ID) \
    Json::ClassRegistrar<TYPE> \
        TYPE::_class_registrar_##ID = Json::ClassRegistrar<TYPE>( string(KEY) );

    
#define UNREGISTER_CLASS(TYPE, NAME) \
    Json::SOFactory::UnRegister<TYPE>(NAME);    
    
    class SOFactory {
    public:

        static std::shared_ptr<Serializable>CreateObject(string &&key);
        static std::vector<std::shared_ptr<Serializable>> CreateObjectArray(string &&key, const size_t size);

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
        
        template< class T >
        static void UnRegister(string &&key) {
            static_assert(std::is_base_of< Serializable, T >::value, "T must be derived from Serializable");
            Common::StringUtility::ToLower(key);
            
            cm_mutex.lock();
            auto itrObj = cm_objectCreators.find(key);
            if (itrObj != cm_objectCreators.end()) {
                cm_objectCreators.erase(itrObj);
            }
            cm_mutex.unlock();

            
            cm_mutexArr.lock();
            auto itrArr = cm_objectArrayCreators.find(std::move(key));
            if (itrArr != cm_objectArrayCreators.end()) {
                cm_objectArrayCreators.erase(itrArr);
            }
            cm_mutexArr.unlock(); 
        }
        
        static void Clear();
        
    protected:
        SOFactory() = default;

        typedef std::shared_ptr<Serializable> (*FunPtr)(void);
        typedef map< string, FunPtr > ListCreators;

        typedef std::vector<std::shared_ptr<Serializable>> (*FunPtrArr)(const size_t);
        typedef map< string, FunPtrArr > ListCreatorsArr;

        template< class T >
        static std::shared_ptr<Serializable> Create() {
            return std::make_shared<T>();
        }

        template< class T >
        static std::vector< std::shared_ptr<Serializable>> CreateArrary(const size_t size) {
            std::vector< std::shared_ptr<Serializable>> v;
            for (size_t i = 0; i < size; i++) {
                v.push_back(std::make_shared<T>());
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


} /* namespace Json */

#endif /* TINY_JSON_SO_FACTOTY_H */

