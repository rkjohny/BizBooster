/*
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#include <gtest/gtest.h>
#include <cpprest/json.h>
#include <string>
#include <tuple>
#include "Json.h"


// test deserialization of drived class

namespace CmarshalTest {
    namespace JsonTest {
        using namespace web;
        using namespace std;
        using namespace Cmarshal::Json;

        class EmptyClass {
        REGISTER_GETTER_START
            REGISTER_GETTER_END

        REGISTER_SETTER_START
            REGISTER_SETTER_END
        };

        TEST(EmptyClassTest, EmptyObject) {
            using Type = typename Remove_CVR<EmptyClass>::Type;
            auto setters = Type::setters;
            auto getters = Type::setters;
            const size_t lengthGetter = std::tuple_size<decltype(getters)>::value;
            const size_t lengthSetter = std::tuple_size<decltype(setters)>::value;
            std::cout << "lengthGetter = " << lengthGetter << std::endl;
            std::cout << "lengthSetter = " << lengthSetter << std::endl;
            ASSERT_TRUE(lengthGetter == 0);
            ASSERT_TRUE(lengthSetter == 0);

            EmptyClass *emptyObject = new EmptyClass();
            json::value jvalue = json::value::null();

            Cmarshal::Json::FromJson(emptyObject, jvalue);
            ASSERT_TRUE(jvalue.is_null());

            jvalue = Cmarshal::Json::ToJson(emptyObject);
            delete emptyObject;

            ASSERT_FALSE(jvalue.is_null());
            ASSERT_TRUE(jvalue.is_object());
            ASSERT_TRUE(jvalue.as_object().begin() == jvalue.as_object().end());
        }
    }
}