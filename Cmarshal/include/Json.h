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

#ifndef CMARSHAL_JSON_H
#define CMARSHAL_JSON_H

#include <tuple>
#include <cpprest/json.h>
#include "Getter.h"
#include "Setter.h"
#include "Serializer.h"
#include "Deserializer.h"

#include <iostream>

namespace Cmarshal {
    namespace Json {

#define REGISTER_GETTER_START \
        static constexpr auto getters = std::make_tuple(
#define GETTER(CLASS, RETURN_TYPE, NAME, FP) Cmarshal::Json::Getter<CLASS, RETURN_TYPE>(FP, NAME)
#define REGISTER_GETTER_END );


#define REGISTER_SETTER_START \
        static constexpr auto setters = std::make_tuple(
#define SETTER(CLASS, ARG_TYPE, NAME, FP) Cmarshal::Json::Setter<CLASS, ARG_TYPE>(FP, NAME)
#define REGISTER_SETTER_END );


#define REGISTER_GETTER_INCLUDING_BASE_START(BASE_CLASS) \
        static constexpr auto getters = std::tuple_cat(BASE_CLASS::getters, std::make_tuple (
#define REGISTER_GETTER_INCLUDING_BASE_END ));

#define REGISTER_SETTER_INCLUDING_BASE_START(BASE_CLASS) \
        static constexpr auto setters = std::tuple_cat(BASE_CLASS::setters, std::make_tuple (
#define REGISTER_SETTER_INCLUDING_BASE_END ));


/************* Load Librray **************************/

        void LoadLibrary();

        void ReleaseLibrary();

/************************** Serializing *************************/

        template<class T>
        json::value ToJson(const T &&object) {
            return Serializer::ToJson(std::move(object));
        }

        template<class T>
        json::value ToJson(const T &object) {
            return Serializer::ToJson(object);
        }

        template<class T>
        json::value ToJson(const T *object) {
            return Serializer::ToJson(object);
        }

        template<class T>
        json::value ToJson(const T *const *object) {
            return Serializer::ToJson(object);
        }

/************************** Deserializing *************************/
        template<class T>
        void FromJson(T &object, const json::value &jvalue) {
            Deserializer::FromJson(object, jvalue);
        }

        template<class T>
        void FromJson(T *object, const json::value &jvalue) {
            Deserializer::FromJson(object, jvalue);
        }

        template<class T>
        void FromJson(T **object, json::value &jvalue) {
            Deserializer::FromJson(object, jvalue);
        }

    } // namespace Json

} // namespace Cmarshal

#endif /* CMARSHAL_JSON_H */
