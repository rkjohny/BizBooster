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

#ifndef CMARSHAL_JSON_SERIALIZER_H
#define CMARSHAL_JSON_SERIALIZER_H

#include <type_traits>
#include "TypeTratits.h"
#include "Getter.h"
#include "AppCommonDef.h"
#include <cpprest/json.h>
#include <cpprest/details/basic_types.h>
#include <cpprest/asyncrt_utils.h>

#include <iostream>
#include <Wt/WDateTime.h>
#include <boost/optional.hpp>

namespace Cmarshal {
    namespace Json {
        //TODO: web::json::value has move constructor and move assignment operator
        // so the returned vaue will not be copyed.
        // otherwise we should use unique_ptr

        class Serializer {
        private:
            MAKE_STATIC(Serializer);

            
            template<class T>
            static void GetData(const std::unique_ptr<T> &object, web::json::value &jvalue, const char *name) {
                if (object) {
                    jvalue[utility::string_t(U(name))] = ToJson(object);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }
            
            template<class T>
            static void GetData(const std::shared_ptr<T> &object, web::json::value &jvalue, const char *name) {
                if (object) {
                    jvalue[utility::string_t(U(name))] = ToJson(object);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }
            
            template<class T>
            static void GetData(const std::weak_ptr<T> &object, web::json::value &jvalue, const char *name) {
                std::shared_ptr<T> shareObject = object.lock();
                if (shareObject) {
                    jvalue[utility::string_t(U(name))] = ToJson(shareObject);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }
            
            template<class T>
            static void GetData(const boost::optional<T> &object, web::json::value &jvalue, const char *name) {
                if (object) {
                    jvalue[utility::string_t(U(name))] = ToJson(object);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }

            template<class T>
            static void GetData(const Wt::WDateTime &object, web::json::value &jvalue, const char *name) {
                if (!object.isNull()) {
                    jvalue[utility::string_t(U(name))] = ToJson(object);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }

            template<class T>
            static void GetData(const Wt::Dbo::ptr<T> &object, web::json::value &jvalue, const char *name) {
                if (object) {
                    jvalue[utility::string_t(U(name))] = ToJson(object);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }

            template<class T>
            static void GetData(const T &object, web::json::value &jvalue, const char *name) {
                jvalue[utility::string_t(U(name))] = ToJson(object);
            }

            template<class T>
            static void GetData(const T *object, web::json::value &jvalue, const char *name) {
                if (object) {
                    jvalue[utility::string_t(U(name))] = ToJson(object);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }

            template<class T>
            static void GetData(const T *const *object, web::json::value &jvalue, const char *name) {
                if (object && *object) {
                    jvalue[utility::string_t(U(name))] = ToJson(object);
                } else {
                    std::cout << "value is null and will be ignored." << std::endl;
                }
            }

            template<std::size_t iteration, class T>
            static void DoSerialize(T *object, web::json::value &jvalue) {
                using ObjectType = typename Remove_CVRP<T>::Type;
                constexpr auto getter = std::get<iteration>(ObjectType::getters);
                auto getterName = getter.name;
                //using GetterReturnType = typename decltype( getter )::Type;
                auto method = getter.fp;

                std::cout << "Found a getter with name: " << getterName << std::endl;

                const auto &getterReturnedObject = (object->*method)();

                GetData(getterReturnedObject, jvalue, getterName);
            }

            template<std::size_t iteration, class T>
            typename std::enable_if<(iteration > 1), void>::type
            static Serialize(T *object, web::json::value &jvalue) {
                DoSerialize<iteration - 1, T>(object, jvalue);

                Serialize<iteration - 1, T>(object, jvalue);
            }

            template<std::size_t iteration, class T>
            typename std::enable_if<(iteration == 1), void>::type
            static Serialize(T *object, web::json::value &jvalue) {
                DoSerialize<0, T>(object, jvalue);
            }

            /**
             * added to remove compile error.
             * when setters length is 0, it will try to compile with iteration = 0
             */
            template<std::size_t iteration, class T>
            typename std::enable_if<(iteration == 0), void>::type
            static Serialize(T *, web::json::value &) {
            }


        public:

            template<class T>
            typename std::enable_if<std::is_array<T>::value, web::json::value>::type
            static ToJson(const T &&) {
                static_assert(true, "Serialization of array is not supported.");
            }


            //////////////////////////////// Enum ///////////////////

            template<class T>
            typename std::enable_if<std::is_enum<T>::value, web::json::value>::type
            static ToJson(const T &&object) {
                std::cout << "Serializing object: type = enum&&, value = " << object << std::endl;
                return web::json::value(static_cast<int>(object));
            }

            template<class T>
            typename std::enable_if<std::is_enum<T>::value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = enum&, value = " << object << std::endl;
                return web::json::value(static_cast<int>(object));
            }

            template<class T>
            typename std::enable_if<std::is_enum<T>::value, web::json::value>::type
            static ToJson(const T *object) {
                std::cout << "Serializing object: type = enum*, value = " << object << std::endl;
                return web::json::value(static_cast<int>(*object));
            }

            template<class T>
            typename std::enable_if<std::is_enum<T>::value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::cout << "Serializing object: type = enum**, value = " << object << std::endl;
                return web::json::value(static_cast<int>(**object));
            }

            //////////////////////////////// bool ///////////////////

            template<class T>
            typename std::enable_if<Is_Bool<T>::Value, web::json::value>::type
            static ToJson(const T &&object) {
                std::cout << "Serializing object: type = bool&&, value = " << object << std::endl;
                return web::json::value(object);
            }

            template<class T>
            typename std::enable_if<Is_Bool<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = bool&, value = " << object << std::endl;
                return web::json::value(object);
            }

            template<class T>
            typename std::enable_if<Is_Bool<T>::Value, web::json::value>::type
            static ToJson(const T *object) {
                std::cout << "Serializing object: type = bool*, value = " << *object << std::endl;
                return web::json::value(*object);
            }

            template<class T>
            typename std::enable_if<Is_Bool<T>::Value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::cout << "Serializing object: type = bool**, value = " << **object << std::endl;
                return web::json::value(**object);
            }

            ///////////////// char ///////////////////////////////////

            template<class T>
            typename std::enable_if<Is_Char<T>::Value, web::json::value>::type
            static ToJson(const T &&object) {
                std::cout << "Serializing object: type = char&&, value = " << object << std::endl;
                return web::json::value(static_cast<int32_t> (object));
            }

            template<class T>
            typename std::enable_if<Is_Char<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = char&, value = " << object << std::endl;
                return web::json::value(static_cast<int32_t> (object));
            }

            template<class T>
            typename std::enable_if<Is_Char<T>::Value, web::json::value>::type
            static ToJson(const T *object) {
                std::string str = std::string(object);
                utility::string_t str_t = utility::string_t(std::move(str));
                std::cout << "Serializing object: type = char*, value = " << str_t << std::endl;
                return web::json::value(std::move(str_t));
            }

            template<class T>
            typename std::enable_if<Is_Char<T>::Value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::string str = std::string(*object);
                utility::string_t str_t = utility::string_t(std::move(str));
                std::cout << "Serializing object: type = char**, value = " << str_t << std::endl;
                return web::json::value(std::move(str_t));
            }

            ///////////////// integer ///////////////////////////////////

            template<class T>
            typename std::enable_if<Is_Integer<T>::Value, web::json::value>::type
            static ToJson(const T &&object) {
                std::cout << "Serializing object: type = integer&&, value = " << object << std::endl;
                return web::json::value(object);
            }

            template<class T>
            typename std::enable_if<Is_Integer<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = integer&, value = " << object << std::endl;
                return web::json::value(object);
            }

            template<class T>
            typename std::enable_if<Is_Integer<T>::Value, web::json::value>::type
            static ToJson(const T *object) {
                std::cout << "Serializing object: type = integer*, value = " << *object << std::endl;
                return web::json::value(*object);
            }

            template<class T>
            typename std::enable_if<Is_Integer<T>::Value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::cout << "Serializing object: type = integer**, value = " << **object << std::endl;
                return web::json::value(**object);
            }

            /////////////////////   Decimal   ///////////////////////////////////

            template<class T>
            typename std::enable_if<Is_Decimal<T>::Value, web::json::value>::type
            static ToJson(const T &&object) {
                std::cout << "Serializing object: type = decimal&&, value = " << object << std::endl;
                return web::json::value(static_cast<double_t> (object));
            }

            template<class T>
            typename std::enable_if<Is_Decimal<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = decimal&, value = " << object << std::endl;
                return web::json::value(static_cast<double_t> (object));
            }

            template<class T>
            typename std::enable_if<Is_Decimal<T>::Value, web::json::value>::type
            static ToJson(const T *object) {
                std::cout << "Serializing object: type = decimal*, value = " << *object << std::endl;
                return web::json::value(static_cast<double_t> (*object));
            }

            template<class T>
            typename std::enable_if<Is_Decimal<T>::Value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::cout << "Serializing object: type = decimal**, value = " << **object << std::endl;
                return web::json::value(static_cast<double_t> (**object));
            }

            /////////////////////// std::string //////////////////////////////////////

            template<class T>
            typename std::enable_if<Json::Is_String<T>::Value, web::json::value>::type
            static ToJson(T &&object) {
                std::cout << "Serializing object: type = std::string&&, value = " << object << std::endl;
                return web::json::value(utility::string_t(object));
            }

            template<class T>
            typename std::enable_if<Json::Is_String<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = std::string&, value = " << object << std::endl;
                return web::json::value(utility::string_t(object));
            }

            template<class T>
            typename std::enable_if<Json::Is_String<T>::Value, web::json::value>::type
            static ToJson(const T *object) {
                std::cout << "Serializing object: type = std::string*, value = " << *object << std::endl;
                utility::string_t str(*object);
                return web::json::value(std::move(str));
            }

            template<class T>
            typename std::enable_if<Json::Is_String<T>::Value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::cout << "Serializing object: type = std::string**, value = " << **object << std::endl;
                utility::string_t str(**object);
                return web::json::value(std::move(str));
            }

            //////////////////  custom object ////////////////////////

            template<class T>
            typename std::enable_if<Json::Is_Class<T>::Value, web::json::value>::type
            static ToJson(const T &&object) {
                std::cout << "Serializing object: type = class{}&&" << std::endl;
                web::json::value jvalue = web::json::value::object();

                using ObjectType = typename Remove_CVRP<T>::Type;
                auto getters = ObjectType::getters;
                const auto length = std::tuple_size<decltype(getters)>::value;
                if (length > 0) {
                    Serialize<length>(&object, jvalue);
                }
                return jvalue;
            }

            template<class T>
            typename std::enable_if<Json::Is_Class<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = class{}&" << std::endl;
                web::json::value jvalue = web::json::value::object();

                using ObjectType = typename Remove_CVRP<T>::Type;
                auto getters = ObjectType::getters;
                const auto length = std::tuple_size<decltype(getters)>::value;
                if (length > 0) {
                    Serialize<length>(&object, jvalue);
                }
                return jvalue;
            }

            template<class T>
            typename std::enable_if<Json::Is_Class<T>::Value, web::json::value>::type
            static ToJson(const T *object) {
                std::cout << "Serializing object: type = class{}*" << std::endl;
                return ToJson(*object);
            }

            template<class T>
            typename std::enable_if<Json::Is_Class<T>::Value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::cout << "Serializing object: type = class{}**" << std::endl;
                return ToJson(**object);
            }


            //////////////////  std::vector ////////////////////////

            template<class T>
            typename std::enable_if<Json::Is_Vector<T>::Value, web::json::value>::type
            static ToJson(const T &&object) {
                std::cout << "Serializing object: type = std::vector<>&&" << std::endl;
                std::size_t length = object.size();
                web::json::value jvalue = web::json::value::array(length);
                size_t index = 0;

                if (length > 0) {
                    web::json::array &jArray = jvalue.as_array();

                    for (auto &arrValue : object) {
                        jArray[index++] = ToJson(arrValue);
                    }
                }

                return jvalue;
            }

            template<class T>
            typename std::enable_if<Json::Is_Vector<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                std::cout << "Serializing object: type = std::vector<>&" << std::endl;
                std::size_t length = object.size();
                web::json::value jvalue = web::json::value::array(length);
                size_t index = 0;

                if (length > 0) {
                    web::json::array &jArray = jvalue.as_array();

                    for (auto &arrValue : object) {
                        jArray[index++] = ToJson(arrValue);
                    }
                }

                return jvalue;
            }

            template<class T>
            typename std::enable_if<Json::Is_Vector<T>::Value, web::json::value>::type
            static ToJson(const T *object) {
                std::cout << "Serializing object: type = std::vector<>*" << std::endl;
                return ToJson(*object);
            }

            template<class T>
            typename std::enable_if<Json::Is_Vector<T>::Value, web::json::value>::type
            static ToJson(const T *const *object) {
                std::cout << "Serializing object: type = std::vector<>**" << std::endl;
                return ToJson(**object);
            }

            /////////////////////////////// wWt::WDatetime ///////////////////////////////
            template<class T>
            typename std::enable_if<Is_WtDateTime<T>::Value, web::json::value>::type
            static ToJson(const T &&object) {
                Wt::WString wstr = object.toString(); // TODO: default format used
                std::string str = wstr.toUTF8(); // TODO: UTF8 encoding used
                std::cout << "Serializing object: type = Wt::WDate&&, value = " << str << std::endl;
                return web::json::value(str);
            }

            template<class T>
            typename std::enable_if<Is_WtDateTime<T>::Value, web::json::value>::type
            static ToJson(const T &object) {
                Wt::WString wstr = object.toString(); // TODO: default format used
                std::string str = wstr.toUTF8(); // TODO: UTF8 encoding used
                std::cout << "Serializing object: type = Wt::WDate&, value = " << str << std::endl;
                return web::json::value(str);
            }

            ///////////////////// Wt::Dbo::ptr<T> ///////////////////////////////////
            template<class T>
            static web::json::value ToJson(const Wt::Dbo::ptr<T> &&object) {
                std::cout << "Serializing object: type = Wt::Dbo::ptr&&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }

            template<class T>
            static web::json::value ToJson(const Wt::Dbo::ptr<T> &object) {
                std::cout << "Serializing object: type = Wt::Dbo::ptr&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }

            
            ///////////////////// std::unique_ptr<T> ///////////////////////////////////
            template<class T>
            static web::json::value ToJson(const std::unique_ptr<T> &&object) {
                std::cout << "Serializing object: type = std::unique::ptr&&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }

            template<class T>
            static web::json::value ToJson(const std::unique_ptr<T> &object) {
                std::cout << "Serializing object: type = std::unique::ptr&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }
            
            ///////////////////// std::shared_ptr<T> ///////////////////////////////////
            template<class T>
            static web::json::value ToJson(const std::shared_ptr<T> &&object) {
                std::cout << "Serializing object: type = std::shared_ptr&&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }

            template<class T>
            static web::json::value ToJson(const std::shared_ptr<T> &object) {
                std::cout << "Serializing object: type = std::shared_ptr&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }

            
            ///////////////////// std::weak_ptr<T> ///////////////////////////////////
            template<class T>
            static web::json::value ToJson(const std::weak_ptr<T> &&object) {
                std::cout << "Serializing object: type = std::weak::ptr&&" << std::endl;
                auto sharedObject = object.lock();
                if (sharedObject) {
                    return ToJson(*sharedObject);
                }
                return web::json::value();
            }

            template<class T>
            static web::json::value ToJson(const std::weak_ptr<T> &object) {
                std::cout << "Serializing object: type = std::weak_ptr&" << std::endl;
                auto sharedObject = object.lock();
                if (sharedObject) {
                    return ToJson(*sharedObject);
                }
                return web::json::value();
            }

            ///////////////////// boost::optional<T> ///////////////////////////////////
            template<class T>
            static web::json::value ToJson(const boost::optional<T> &&object) {
                std::cout << "Serializing object: type = Wt::Dbo::ptr&&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }

            template<class T>
            static web::json::value ToJson(const boost::optional<T> &object) {
                std::cout << "Serializing object: type = Wt::Dbo::ptr&&" << std::endl;
                if (object) {
                    return ToJson(*object);
                }
                return web::json::value();
            }
        };

    } // namespace Json
} // namespace Cmarshal

#endif // CMARSHAL_JSON_SERIALIZER_H
