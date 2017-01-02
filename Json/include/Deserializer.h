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

#ifndef TINY_JSON_DESERIALIZER_H
#define TINY_JSON_DESERIALIZER_H

#include <cpprest/json.h>
#include "TypeTratits.h"
#include "AppDef.h"
#include <iostream>
#include <Wt/WDateTime>

namespace Json {
    using namespace web;

    class Deserializer {
    private:
        MAKE_STATIC(Deserializer);


        /**
         * calls the setter method with type = Wt::Dbo::ptr<T>
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void (B::*SetterPtr)(const Wt::Dbo::ptr<ArgT> &), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(const ArgT)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Wt::Dbo::ptr<Type> var = Wt::Dbo::ptr<Type>(new Type());
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with rvalue reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT&&), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(ArgT&&)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jvalue);
            (object->*SetterPtr)(std::move(var));
        }


        /**
         * calls the setter method with rvalue reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT&&), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(const ArgT&&)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jvalue);
            (object->*SetterPtr)(std::move(var));
        }

        /**
         * calls the setter method with value type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(const ArgT)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT&), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(ArgT&)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant reference type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT&), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(const ArgT&)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type var;
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * special handling for char array.
         * No other array type is supported. 
         */
        template<class T, class B>
        static void SetData(T *object, void ( B::*SetterPtr)(char*), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(ArgT*)" << std::endl;
            char *var;
            FromJson(&var, jvalue);
            (object->*SetterPtr)(var);
        }
        
        /**
         * special handling for char array.
         * No other array type is supported. 
         */
        template<class T, class B>
        static void SetData(T *object, void ( B::*SetterPtr)(const char*), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(ArgT*)" << std::endl;
            char *var;
            FromJson(&var, jvalue);
            (object->*SetterPtr)(var);
        }
        
        /**
         * calls the setter method with pointer type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT*), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(ArgT*)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type *var = new Type();
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant pointer type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT*), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(const ArgT*)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type *var = new Type();
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant pointer type argument
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(ArgT**), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(ArgT**)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type **var = new Type * ();
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * calls the setter method with constant pointer type argument
         * TODO: make first level const, i.e const ArgT* const*
         */
        template<class T, class B, class ArgT>
        static void SetData(T *object, void ( B::*SetterPtr)(const ArgT* const*), const json::value &jvalue) {
            std::cout << "Setdata : void (T::*SetterPtr)(const ArgT**)" << std::endl;

            using Type = typename Remove_CVR<ArgT>::Type;

            Type **var = new Type * ();
            FromJson(var, jvalue);
            (object->*SetterPtr)(var);
        }

        /**
         * get the setter at tuple position referenced by iteratiorn.
         * call the setter to set the value to the object'c property.
         */
        template<size_t iteration, class T>
        static void DoDeserialize(T *object, const json::value &jvalue) {
            using Type = typename Remove_CVR<T>::Type;
            auto setters = Type::setters;
            auto setter = std::get<iteration> (setters);

            using ClassT = typename Remove_CVR< typename decltype(setter) ::Class >::Type;
            //using ArgT = typename decltype( setter ) ::Type;
            auto name = setter.name;
            auto fp = setter.fp;

            std::cout << "Found a setter with name: " << name << std::endl;
            bool found = false;

            if (jvalue.has_field(U(name))) {
                const auto &jval = jvalue.at(U(name));

                if (!jval.is_null()) {
                    found = true;
                    // either Type and ClassT are same type or ClassT is base of Type
                    SetData<Type, ClassT> (object, fp, jval);
                }
            }

            if (!found) {
                std::cout << "value is null and will be ignored." << std::endl;
            }
        }

        /**
         * execute the setter at position greater than 0
         */
        template<size_t iteration, class T>
        typename std::enable_if < (iteration > 1), void >::type
        static Deserialize(T *object, const json::value &jvalue) {
            DoDeserialize < iteration - 1 > (object, jvalue);

            Deserialize < iteration - 1 > (object, jvalue);
        }

        /**
         * execute the setter at position 0
         */
        template<size_t iteration, class T>
        typename std::enable_if< (iteration == 1), void>::type
        static Deserialize(T *object, const json::value &jvalue) {
            DoDeserialize<0> (object, jvalue);
        }

        /**
         * added to remove compile error.
         * when setters length is 0, it will try to compile with iteration = 0
         */
        template<size_t iteration, class T>
        typename std::enable_if< (iteration == 0), void>::type
        static Deserialize(T *, const json::value &) {
        }

    public:

        /**
         * object is constant reference, return error
         */
        template<class T>
        typename std::enable_if<std::is_const<T>::value, void>::type
        FromJson(T &) {
            static_assert(true, "object cannot be constant");
        }

        /**
         * object is constant pointer, return error
         */
        template<class T>
        typename std::enable_if<std::is_const<T>::value, void>::type
        FromJson(T *) {
            static_assert(true, "object pointer cannot be constant");
        }

        /**
         * object is constant reference, return error
         */
        template<class T>
        typename std::enable_if<std::is_array<T>::value, void>::type
        FromJson(T &) {
            static_assert(true, "Deserialization of array is not supported.");
        }



        /********************************************************************************
         * object type: enum
         ********************************************************************************/
        template<class T>
        typename std::enable_if<std::is_enum<T>::value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            object = static_cast<T>(jvalue.as_integer());
            std::cout << "Deserializing object: type = Enum&, value = " << object << std::endl;
        }

        /********************************************************************************
         * object type: enum*
         ********************************************************************************/
        template<class T>
        typename std::enable_if<std::is_enum<T>::value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = static_cast<T>(jvalue.as_integer());
            std::cout << "Deserializing object: type = Enum*, value = " << *object << std::endl;
        }

        /********************************************************************************
         * object type: enum**
         ********************************************************************************/
        template<class T>
        typename std::enable_if<std::is_enum<T>::value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            //*object = static_cast<T>(jvalue.as_integer());
            *object = new T (static_cast<T>(jvalue.as_integer()));
            std::cout << "Deserializing object: type = Enum*, value = " << *object << std::endl;
        }

        /*********************************************************************************
         * object type: bool
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            object = jvalue.as_bool();
            std::cout << "Deserializing object: type = Bool&, value = " << object << std::endl;
        }

        /*********************************************************************************
         * object type: bool*
         * object should be allocated;
         *
         * example of usages:
         *
         *      json::value jvalue = json::value(true);
         *
         * example1:
         *      bool bvalue;
         *      Json::FromJson(&bvalue, jvalue);
         *
         * example2:
         *      bool *p = new bool();
         *      Json::FromJson(p, jvalue); // p will NOT be allocated
         *      delete p;
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = jvalue.as_bool();
            std::cout << "Deserializing object: type = Bool*, value = " << *object << std::endl;
        }

        /*********************************************************************************
         * object type: bool*
         * object should NOT be allocated;
         *
         * example of usages:
         *
         *      json::value jvalue = json::value(true);
         *
         * example1:
         *      bool *p = nullptr;
         *      Json::FromJson(&p, jvalue); // *p will be allocated
         *      if (p)
         *          delete p;
         *
         * example2:
         *      bool **p = new bool*();
         *      Json::FromJson(p, jvalue); // *p will be allocated
         *      if (*p)
         *          delete *p;
         *      if (p)
         *          delete p;
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Bool<T>::Value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            *object = new bool ( jvalue.as_bool());
            std::cout << "Deserializing object: type = Bool**, value = " << **object << std::endl;
        }

        /*********************************************************************************
         * object type: char
         *********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Char<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            object = jvalue.as_integer();
            std::cout << "Deserializing object: type = char&, value = " << object << std::endl;
        }

        /**********************************************************************************
         * type: char*
         *
         * see usges of for bool*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Char<T>::Value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            const utility::string_t &strT = jvalue.as_string();
            std::string str = utility::conversions::to_utf8string(strT);
            strcpy(object, str.c_str());
            std::cout << "Deserializing object: type = char*, value = " << object << std::endl;
        }

        /**********************************************************************************
         * type: char**
         *
         * see usages for bool**
         *
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Char<T>::Value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            const utility::string_t &strT = jvalue.as_string();
            std::string str = utility::conversions::to_utf8string(strT);
            *object = new char [str.length() + 1];
            strcpy(*object, str.c_str());
            std::cout << "Deserializing object: type = char**, value = " << *object << std::endl;
        }

        /***********************************************************************************
         * object type: int8_t, int16_t, int32_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if < Is_Int8<T>::Value || Is_Int16<T>::Value || Is_Int32<T>::Value, void >::type
        static FromJson(T &object, const json::value &jvalue) {
            object = static_cast<T> (jvalue.as_number().to_int32());
            std::cout << "Deserializing object: type = signed integer32&, value = " << (int32_t) object << std::endl;
        }

        /***********************************************************************************
         * object type: int8_t*, int16_t*, int32_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if < Is_Int8<T>::Value || Is_Int16<T>::Value || Is_Int32<T>::Value, void >::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = static_cast<T> (jvalue.as_number().to_int32());
            std::cout << "Deserializing object: type = signed integer32*, value = " << (int32_t) * object << std::endl;
        }

        /***********************************************************************************
         * object type: int8_t**, int16_t**, int32_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if < Is_Int8<T>::Value || Is_Int16<T>::Value || Is_Int32<T>::Value, void >::type
        static FromJson(T **object, const json::value &jvalue) {
            *object = new typename Remove_CVR<T>::Type(static_cast<T> (jvalue.as_number().to_int32()));
            std::cout << "Deserializing object: type = signed integer32**, value = " << (int32_t)**object << std::endl;
        }

        /***********************************************************************************
         * object type: uint8_t, uint16_t, uint32_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if < Is_UInt8<T>::Value || Is_UInt16<T>::Value || Is_UInt32<T>::Value, void >::type
        static FromJson(T &object, const json::value &jvalue) {
            object = static_cast<T> (jvalue.as_number().to_uint32());
            std::cout << "Deserializing object: type = unsigned integer32&, value = " << (uint32_t) object << std::endl;
        }

        /***********************************************************************************
         * object type: uint8_t*, uint16_t*, uint32_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if < Is_UInt8<T>::Value || Is_UInt16<T>::Value || Is_UInt32<T>::Value, void >::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = static_cast<T> (jvalue.as_number().to_uint32());
            std::cout << "Deserializing object: type = unsigned integer32*, value = " << (uint32_t) * object << std::endl;
        }

        /***********************************************************************************
         * object type: uint8_t**, uint16_t**, uint32_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if < Is_UInt8<T>::Value || Is_UInt16<T>::Value || Is_UInt32<T>::Value, void >::type
        static FromJson(T **object, const json::value &jvalue) {

            *object = new typename Remove_CVR<T>::Type(static_cast<T> (jvalue.as_number().to_uint32()));
            std::cout << "Deserializing object: type = unsigned integer32**, value = " << (uint32_t)**object << std::endl;
        }

        /***********************************************************************************
         * object type: int64_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int64<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            object = jvalue.as_number().to_int64();
            std::cout << "Deserializing object: type = signed integer64&, value = " << object << std::endl;
        }

        /***********************************************************************************
         * object type: int64_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int64<T>::Value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = jvalue.as_number().to_int64();
            std::cout << "Deserializing object: type = signed integer64*, value = " << *object << std::endl;
        }

        /***********************************************************************************
         * object type: int64_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Int64<T>::Value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            *object = new int64_t(jvalue.as_number().to_int64());
            std::cout << "Deserializing object: type = signed integer64**, value = " << **object << std::endl;
        }

        /***********************************************************************************
         * object type: uint64_t
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt64<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            object = jvalue.as_number().to_uint64();
            std::cout << "Deserializing object: type = unsigned integer64&, value = " << object << std::endl;
        }

        /***********************************************************************************
         * object type: uint64_t*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt64<T>::Value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = jvalue.as_number().to_uint64();
            std::cout << "Deserializing object: type = unsigned integer64*, value = " << *object << std::endl;
        }

        /***********************************************************************************
         * object type: uint64_t**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_UInt64<T>::Value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            *object = new uint64_t(jvalue.as_number().to_uint64());
            std::cout << "Deserializing object: type = unsigned integer64**, value = " << **object << std::endl;
        }

        /***********************************************************************************
         * object type: float, double, long double
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            object = static_cast<T> (jvalue.as_number().to_double());
            std::cout << "Deserializing object: type = decimal&, value = " << object << std::endl;
        }

        /***********************************************************************************
         * object type: float*, double*, long double*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = static_cast<T> (jvalue.as_number().to_double());
            std::cout << "Deserializing object: type = decimal*, value = " << *object << std::endl;
        }

        /***********************************************************************************
         * object type: float**, double**, long double**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Decimal<T>::Value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            *object = new typename Remove_CVR<T>::Type(static_cast<T> (jvalue.as_number().to_double()));
            std::cout << "Deserializing object: type = decimal**, value = " << **object << std::endl;
        }

        /***********************************************************************************
         * object type: std::string
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_String<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            object = utility::conversions::to_utf8string(jvalue.as_string());
            std::cout << "Deserializing object: type = std::string&, value = " << object << std::endl;
        }

        /***********************************************************************************
         * object type: std::string*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_String<T>::Value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            *object = utility::conversions::to_utf8string(jvalue.as_string());
            std::cout << "Deserializing object: type = std::string*, value = " << *object << std::endl;
        }

        /***********************************************************************************
         * object type: std::string**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_String<T>::Value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            *object = new std::string(utility::conversions::to_utf8string(jvalue.as_string()));
            std::cout << "Deserializing object: type = std::string**, value = " << **object << std::endl;
        }


        /*///////////////////////////  OBJECT ////////////////////////////////////////////*/

        /***********************************************************************************
         * object type: userdefined class{}*
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Class<T>::Value, void>::type
        static FromJson(T *object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = class{}*" << std::endl;

            using Type = typename Remove_CVR<T>::Type;
            auto setters = Type::setters;
            const auto length = std::tuple_size < decltype(setters) >::value;
            if (length > 0) {
                Deserialize < length > (object, jvalue);
            }
        }

        /***********************************************************************************
         * object type: userdefined class{}&
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Class<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = class{}&" << std::endl;

            FromJson(&object, jvalue);
        }

        /***********************************************************************************
         * object type: userdefined class{}**
         ***********************************************************************************/
        template<class T>
        typename std::enable_if<Is_Class<T>::Value, void>::type
        static FromJson(T **object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = class{}**" << std::endl;

            using Type = typename Remove_CVR<T>::Type;
            *object = new Type();

            FromJson(*object, jvalue);
        }


        /*///////////////////////////  VECTOR ////////////////////////////////////////////*/

        /***********************************************************************************
         * special handling for vector of char*
         ***********************************************************************************/
        static void FromJson(std::vector<char*> *object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T>*" << std::endl;
            for (const auto &arrItem : jvalue.as_array()) {
                //char *var = new char[arrItem.size()];
                char *var;
                FromJson(&var, arrItem);
                object->push_back(var);
            }
        }
        static void FromJson(std::vector<const char*> *object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T>*" << std::endl;
            for (const auto &arrItem : jvalue.as_array()) {
                //char *var = new char[arrItem.size()];
                char *var;
                FromJson(&var, arrItem);
                object->push_back(var);
            }
        }
        
        /***********************************************************************************
         * object type: std::vector<T*>*
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T*> *object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T*>*" << std::endl;

            using Type = typename Remove_CVR<T>::Type;

            for (const auto &arrItem : jvalue.as_array()) {
                Type *var = new Type();
                FromJson(var, arrItem);
                object->push_back(var);
            }
        }

        /***********************************************************************************
         * object type: std::vector<T*>&
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T*> &object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T*>&" << std::endl;

            FromJson(&object, jvalue);
        }

        /***********************************************************************************
         * object type: std::vector<T*>**
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T*> **object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T*>*" << std::endl;

            //using Type = typename Remove_CVR<T>::Type;
            *object = new std::vector<T*>();

            FromJson(*object, jvalue);
        }

        /***********************************************************************************
         * object type: std::vector<T>*
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T> *object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T>*" << std::endl;

            using Type = typename Remove_CVR<T>::Type;

            for (const auto &arrItem : jvalue.as_array()) {
                Type var = Type();
                FromJson(var, arrItem);
                object->push_back(var);
            }
        }

        /***********************************************************************************
         * object type: std::vector<T>&
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T> &object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T>&" << std::endl;

            FromJson(&object, jvalue);
        }

        /***********************************************************************************
         * object type: std::vector<T>**
         ***********************************************************************************/
        template<class T>
        static void FromJson(std::vector<T> **object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = vector<T>*" << std::endl;

            //using Type = typename Remove_CVR<T>::Type;
            *object = new std::vector<T>();

            FromJson(*object, jvalue);
        }

        /***********************************************************************************
        * object type: Wt::Dbo::ptr<T>
        ***********************************************************************************/
        template<class T>
        static void FromJson(Wt::Dbo::ptr<T> &object, const json::value &jvalue) {
            std::cout << "Deserializing object: type = Wt::Dbo::ptr<T> &" << std::endl;
            FromJson(const_cast<T*>(object.get()), jvalue);
        }

        /********************************************************************************
         * object type: Wt::WDateTime
         ********************************************************************************/
        template<class T>
        typename std::enable_if<Is_DateTime<T>::Value, void>::type
        static FromJson(T &object, const json::value &jvalue) {
            const utility::string_t &dateTimeStr = jvalue.as_string();
            //TODO: default encoding and format used
            object = Wt::WDateTime::fromString(utility::conversions::to_utf8string(dateTimeStr));
            std::cout << "Deserializing object: type = Wt::WDateTime&, value = " << dateTimeStr << std::endl;
        }
    };

} //namspace Json

#endif //TINY_JSON_DESERIALIZER_H
