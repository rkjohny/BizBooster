/**
 * Author: Rezaul Karm
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#ifndef _TINY_JSON_H_
#define _TINY_JSON_H_

#include <tuple>
#include <cpprest/json.h>
#include "Getter.h"
#include "Setter.h"
#include "Serializer.h"
#include "Deserializer.h"

#include <iostream>

namespace Json {

#define REGISTER_GETTER_START \
        public: static constexpr auto getters = std::make_tuple(
#define GETTER(CLASS, RETURN_TYPE, NAME, FP) Json::Getter<CLASS, RETURN_TYPE>(FP, NAME)
#define REGISTER_GETTER_END );


#define REGISTER_SETTER_START \
        public: static constexpr auto setters = std::make_tuple(
#define SETTER(CLASS, ARG_TYPE, NAME, FP) Json::Setter<CLASS, ARG_TYPE>(FP, NAME)
#define REGISTER_SETTER_END );


#define REGISTER_GETTER_INCLUDING_BASE_START(BASE_CLASS) \
        public: static constexpr auto getters = std::tuple_cat(BASE_CLASS::getters, std::make_tuple (
#define REGISTER_GETTER_INCLUDING_BASE_END ));

#define REGISTER_SETTER_INCLUDING_BASE_START(BASE_CLASS) \
        public: static constexpr auto setters = std::tuple_cat(BASE_CLASS::setters, std::make_tuple (
#define REGISTER_SETTER_INCLUDING_BASE_END ));


    /************* Load Librray **************************/
    void LoadLibrary();

    /************************** Serializing *************************/
    template <class T>
    json::value ToJson(const T &&object) {
        return Serializer::ToJson(std::move(object));
    }

    template <class T>
    json::value ToJson(const T &object) {
        return Serializer::ToJson(object);
    }

    template <class T>
    json::value ToJson(const T *object) {
        return Serializer::ToJson(object);
    }

    template <class T>
    json::value ToJson(const T* const *object) {
        return Serializer::ToJson(object);
    }

    /************************** Deserializing *************************/
    template<class T>
    void FromJson(T &object, const json::value &jvalue) {
        Deserializer::FromJson(object, jvalue);
    }

    template<class T>
    void FromJson(T *object, const json::value &jvalue) {
        //std::cout << "Json::FromJson T*" <<std::endl;
        Deserializer::FromJson(object, jvalue);
    }

    template<class T>
    void FromJson(T **object, json::value &jvalue) {
        //std::cout << "Json::FromJson T** <<std::endl;
        Deserializer::FromJson(object, jvalue);
    }

} // namespace Json

#endif
