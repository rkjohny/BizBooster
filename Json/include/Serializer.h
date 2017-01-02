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

#ifndef TINY_JSON_SERIALIZER_H
#define TINY_JSON_SERIALIZER_H

#include <type_traits>
#include "TypeTratits.h"
#include "Getter.h"
#include "AppDef.h"
#include <cpprest/json.h>
#include <cpprest/details/basic_types.h>
#include <cpprest/asyncrt_utils.h>

#include <iostream>
#include <Wt/WDateTime>

namespace Json {
    using namespace web;
    using namespace std;

    //TODO: json::value has move constructor and move assignment operator
    // so the returned vaue will not be copyed.
    // otherwise we should use unique_ptr

    class Serializer {
    private:
        MAKE_STATIC(Serializer);

        template<class T>
        static void GetData(const Wt::WDateTime &object, json::value &jvalue, const char*name) {
            if (!object.isNull()) {
                jvalue[utility::string_t(U(name))] = ToJson(object);
            } else {
                cout << "value is null and will be ignored." << endl;
            }
        }

        template<class T>
        static void GetData(const Wt::Dbo::ptr<T> &object, json::value &jvalue, const char*name) {
            if (object.get()) {
                jvalue[utility::string_t(U(name))] = ToJson(object);
            } else {
                cout << "value is null and will be ignored." << endl;
            }
        }

        template<class T>
        static void GetData(const T &object, json::value &jvalue, const char*name) {
            jvalue[utility::string_t(U(name))] = ToJson(object);
        }

        template<class T>
        static void GetData(const T *object, json::value &jvalue, const char*name) {
            if (object) {
                jvalue[utility::string_t(U(name))] = ToJson(object);
            } else {
                cout << "value is null and will be ignored." << endl;
            }
        }

        template<class T>
        static void GetData(const T * const *object, json::value &jvalue, const char*name) {
            if (object && *object) {
                jvalue[utility::string_t(U(name))] = ToJson(object);
            } else {
                cout << "value is null and will be ignored." << endl;
            }
        }

        template<std::size_t iteration, class T>
        static void DoSerialize(T* object, json::value &jvalue) {
            using ObjectType = typename Remove_CVRP<T>::Type;
            constexpr auto getter = std::get<iteration>(ObjectType::getters);
            auto getterName = getter.name;
            //using GetterReturnType = typename decltype( getter )::Type;
            auto method = getter.fp;

            auto getterReturnedObject = (object->*method)();

            cout << "Found a getter with name: " << getterName << std::endl;

            GetData(getterReturnedObject, jvalue, getterName);
        }

        template<std::size_t iteration, class T>
        typename std::enable_if < (iteration > 1), void >::type
        static Serialize(T* object, json::value &jvalue) {
            DoSerialize < iteration - 1, T > (object, jvalue);

            Serialize < iteration - 1, T > (object, jvalue);
        }

        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 1), void>::type
        static Serialize(T* object, json::value &jvalue) {
            DoSerialize<0, T>(object, jvalue);
        }

        /**
         * added to remove compile error.
         * when setters length is 0, it will try to compile with iteration = 0
         */
        template<std::size_t iteration, class T>
        typename std::enable_if<(iteration == 0), void>::type
        static Serialize(T*, json::value&) {
        }


    public:

        template <class T>
        typename std::enable_if<std::is_array<T>::value, json::value>::type
        static ToJson(const T &&) {
            static_assert(true, "Serialization of array is not supported.");
        }


        //////////////////////////////// Enum ///////////////////

        template <class T>
        typename std::enable_if<std::is_enum<T>::value, json::value>::type
        static ToJson(const T &&object) {
            cout << "Serializing object: type = enum&&, value = " << object << endl;
            return json::value(static_cast<int>(object));
        }

        template <class T>
        typename std::enable_if<std::is_enum<T>::value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = enum&, value = " << object << endl;
            return json::value(static_cast<int>(object));
        }

        template <class T>
        typename std::enable_if<std::is_enum<T>::value, json::value>::type
        static ToJson(const T *object) {
            cout << "Serializing object: type = enum*, value = " << object << endl;
            return json::value(static_cast<int>(*object));
        }

        template <class T>
        typename std::enable_if<std::is_enum<T>::value, json::value>::type
        static ToJson(const T* const *object) {
            cout << "Serializing object: type = enum**, value = " << object << endl;
            return json::value(static_cast<int>(**object));
        }

        //////////////////////////////// bool ///////////////////

        template <class T>
        typename std::enable_if<Is_Bool<T>::Value, json::value>::type
        static ToJson(const T &&object) {
            cout << "Serializing object: type = bool&&, value = " << object << endl;
            return json::value(object);
        }

        template <class T>
        typename std::enable_if<Is_Bool<T>::Value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = bool&, value = " << object << endl;
            return json::value(object);
        }

        template <class T>
        typename std::enable_if<Is_Bool<T>::Value, json::value>::type
        static ToJson(const T *object) {
            cout << "Serializing object: type = bool*, value = " << *object << endl;
            return json::value(*object);
        }

        template <class T>
        typename std::enable_if<Is_Bool<T>::Value, json::value>::type
        static ToJson(const T * const * object) {
            cout << "Serializing object: type = bool**, value = " << **object << endl;
            return json::value(**object);
        }

        ///////////////// char ///////////////////////////////////

        template <class T>
        typename std::enable_if<Is_Char<T>::Value, json::value>::type
        static ToJson(const T &&object) {
            cout << "Serializing object: type = char&&, value = " << object << endl;
            return json::value(static_cast<int32_t> (object));
        }

        template <class T>
        typename std::enable_if<Is_Char<T>::Value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = char&, value = " << object << endl;
            return json::value(static_cast<int32_t> (object));
        }

        template <class T>
        typename std::enable_if<Is_Char<T>::Value, json::value>::type
        static ToJson(const T *object) {
            auto str = std::string(object);
            auto str_t = utility::string_t(std::move(str));
            cout << "Serializing object: type = char*, value = " << str_t << endl;
            return json::value(std::move(str_t));
        }

        template <class T>
        typename std::enable_if<Is_Char<T>::Value, json::value>::type
        static ToJson(const T * const * object) {
            auto str = std::string(*object);
            auto str_t = utility::string_t(std::move(str));
            cout << "Serializing object: type = char**, value = " << str_t << endl;
            return json::value(std::move(str_t));
        }

        ///////////////// integer ///////////////////////////////////

        template <class T>
        typename std::enable_if<Is_Integer<T>::Value, json::value>::type
        static ToJson(const T &&object) {
            cout << "Serializing object: type = integer&&, value = " << object << endl;
            return json::value(object);
        }

        template <class T>
        typename std::enable_if<Is_Integer<T>::Value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = integer&, value = " << object << endl;
            return json::value(object);
        }

        template <class T>
        typename std::enable_if<Is_Integer<T>::Value, json::value>::type
        static ToJson(const T *object) {
            cout << "Serializing object: type = integer*, value = " << *object << endl;
            return json::value(*object);
        }

        template <class T>
        typename std::enable_if<Is_Integer<T>::Value, json::value>::type
        static ToJson(const T * const * object) {
            cout << "Serializing object: type = integer**, value = " << **object << endl;
            return json::value(**object);
        }

        /////////////////////   Decimal   ///////////////////////////////////

        template <class T>
        typename std::enable_if<Is_Decimal<T>::Value, json::value>::type
        static ToJson(const T &&object) {
            cout << "Serializing object: type = decimal&&, value = " << object << endl;
            return json::value(static_cast<double_t> (object));
        }

        template <class T>
        typename std::enable_if<Is_Decimal<T>::Value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = decimal&, value = " << object << endl;
            return json::value(static_cast<double_t> (object));
        }

        template <class T>
        typename std::enable_if<Is_Decimal<T>::Value, json::value>::type
        static ToJson(const T *object) {
            cout << "Serializing object: type = decimal*, value = " << *object << endl;
            return json::value(static_cast<double_t> (*object));
        }

        template <class T>
        typename std::enable_if<Is_Decimal<T>::Value, json::value>::type
        static ToJson(const T * const *object) {
            cout << "Serializing object: type = decimal**, value = " << **object << endl;
            return json::value(static_cast<double_t> (**object));
        }

        /////////////////////// std::string //////////////////////////////////////

        template <class T>
        typename std::enable_if<Json::Is_String<T>::Value, json::value>::type
        static ToJson(T &&object) {
            cout << "Serializing object: type = std::string&&, value = " << object << endl;
            return json::value(utility::string_t(object));
        }

        template <class T>
        typename std::enable_if<Json::Is_String<T>::Value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = std::string&, value = " << object << endl;
            return json::value(utility::string_t(object));
        }

        template <class T>
        typename std::enable_if<Json::Is_String<T>::Value, json::value>::type
        static ToJson(const T *object) {
            cout << "Serializing object: type = std::string*, value = " << *object << endl;
            utility::string_t str(*object);
            return json::value(std::move(str));
        }

        template <class T>
        typename std::enable_if<Json::Is_String<T>::Value, json::value>::type
        static ToJson(const T * const * object) {
            cout << "Serializing object: type = std::string**, value = " << **object << endl;
            utility::string_t str(**object);
            return json::value(std::move(str));
        }

        //////////////////  custom object ////////////////////////

        template <class T>
        typename std::enable_if<Json::Is_Class<T>::Value, json::value>::type
        static ToJson(const T &&object) {
            cout << "Serializing object: type = class{}&&" << endl;
            auto jvalue = json::value::object();

            using ObjectType = typename Remove_CVRP<T>::Type;
            auto getters = ObjectType::getters;
            const auto length = std::tuple_size < decltype(getters)>::value;
            if (length > 0) {
                Serialize < length > (&object, jvalue);
            }
            return jvalue;
        }

        template <class T>
        typename std::enable_if<Json::Is_Class<T>::Value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = class{}&" << endl;
            auto jvalue = json::value::object();

            using ObjectType = typename Remove_CVRP<T>::Type;
            auto getters = ObjectType::getters;
            const auto length = std::tuple_size < decltype(getters)>::value;
            if (length > 0) {
                Serialize < length > (&object, jvalue);
            }
            return jvalue;
        }

        template <class T>
        typename std::enable_if<Json::Is_Class<T>::Value, json::value>::type
        static ToJson(const T *object) {
            cout << "Serializing object: type = class{}*" << endl;
            return ToJson(*object);
        }

        template <class T>
        typename std::enable_if<Json::Is_Class<T>::Value, json::value>::type
        static ToJson(const T * const * object) {
            cout << "Serializing object: type = class{}**" << endl;
            return ToJson(**object);
        }


        //////////////////  std::vector ////////////////////////

        template <class T>
        typename std::enable_if<Json::Is_Vector<T>::Value, json::value>::type
        static ToJson(const T &&object) {
            cout << "Serializing object: type = std::vector<>&&" << endl;
            auto length = object.size();
            auto jvalue = json::value::array(length);
            size_t index = 0;

            if (length > 0) {
                auto jArray = jvalue.as_array();

                for (auto& arrValue : object) {
                    jArray[index++] = ToJson(arrValue);
                }
            }

            return jvalue;
        }

        template <class T>
        typename std::enable_if<Json::Is_Vector<T>::Value, json::value>::type
        static ToJson(const T &object) {
            cout << "Serializing object: type = std::vector<>&" << endl;
            auto length = object.size();
            auto jvalue = json::value::array(length);
            size_t index = 0;

            if (length > 0) {
                auto jArray = jvalue.as_array();

                for (auto& arrValue : object) {
                    jArray[index++] = ToJson(arrValue);
                }
            }

            return jvalue;
        }

        template <class T>
        typename std::enable_if<Json::Is_Vector<T>::Value, json::value>::type
        static ToJson(const T *object) {
            cout << "Serializing object: type = std::vector<>*" << endl;
            return ToJson(*object);
        }

        template <class T>
        typename std::enable_if<Json::Is_Vector<T>::Value, json::value>::type
        static ToJson(const T * const * object) {
            cout << "Serializing object: type = std::vector<>**" << endl;
            return ToJson(**object);
        }


        ///////////////////// Wt::Dbo::ptr<T> ///////////////////////////////////
        template <class T>
        static json::value ToJson(const Wt::Dbo::ptr<T> &&object)
        {
            cout << "Serializing object: type = Wt::Dbo::ptr&&" << endl;
            return ToJson(*object);
        }
        template <class T>
        static json::value ToJson(const Wt::Dbo::ptr<T> &object)
        {
            cout << "Serializing object: type = Wt::Dbo::ptr&" << endl;
            return ToJson(*object);
        }

        /////////////////////////////// wWt::WDatetime ///////////////////////////////
        template <class T>
        typename std::enable_if<Is_DateTime<T>::Value, json::value>::type
        static ToJson(const T &&object) {
            auto wstr = object.toString(); // TODO: default format used
            auto str = wstr.toUTF8(); // TODO: UTF8 encoding used
            cout << "Serializing object: type = Wt::WDate&&, value = " << str << endl;
            return json::value(str);
        }
        template <class T>
        typename std::enable_if<Is_DateTime<T>::Value, json::value>::type
        static ToJson(const T &object) {
            auto wstr = object.toString(); // TODO: default format used
            auto str = wstr.toUTF8(); // TODO: UTF8 encoding used
            cout << "Serializing object: type = Wt::WDate&, value = " << str << endl;
            return json::value(str);
        }
    };

} // namespace Json

#endif // TINY_JSON_SERIALIZER_H
