/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */


#include <gtest/gtest.h>
#include <cpprest/json.h>
#include <string>
#include "Json.h"
#include <tuple>
#include <iostream>
#include "TypeTratits.h"

using namespace web;
using namespace std;
using namespace Json;


namespace JsonTest
{

class EmptyClass
{
    REGISTER_GETTER_START
    REGISTER_GETTER_END

    REGISTER_SETTER_START
    REGISTER_SETTER_END
};

TEST(EmptyClassTest, EmptyTest)
{
    json::value jvalue = json::value::null();

    EmptyClass *emptyObject = new EmptyClass();

    using Type = typename Remove_CVR<EmptyClass>::Type;
    auto setters = Type::setters;
    auto getters = Type::setters;

    const size_t lengthGetter = std::tuple_size<decltype(getters)>::value;
    const size_t lengthSetter = std::tuple_size<decltype(setters)>::value;

    std::cout << "lengthGetter = " << lengthGetter << std::endl;
    std::cout << "lengthSetter = " << lengthSetter << std::endl;

    ASSERT_TRUE(lengthGetter == 0);
    ASSERT_TRUE(lengthSetter == 0);

    Json::FromJson(emptyObject, jvalue);

    ASSERT_TRUE( jvalue.is_null() );

    jvalue = Json::ToJson(emptyObject);

    ASSERT_FALSE( jvalue.is_null() );
    ASSERT_TRUE( jvalue.is_object() );
    bool isEmpty = true;
    for(auto &item : jvalue.as_object())
    {
        isEmpty = false;
    }
    ASSERT_TRUE(isEmpty);
}

}


