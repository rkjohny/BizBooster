

#include <gtest/gtest.h>
#include <cpprest/json.h>
#include "Json.h"

namespace CmarshalTest {
    namespace JsonTest {
        enum EnumTest {
            A = 10,
            B = 20,
            C = 30,
        };

        TEST(SerializeEnumTest, ValueType) {
            EnumTest enm;
            web::json::value jval = web::json::value::number(static_cast<int>(EnumTest::B));
            Cmarshal::Json::FromJson(enm, jval);
            ASSERT_TRUE(jval.as_integer() == static_cast<int>(EnumTest::B));
        }

        TEST(DeserializeEnumTest, ValueType) {
            EnumTest enm = EnumTest::B;
            web::json::value jval = Cmarshal::Json::ToJson(enm);
            ASSERT_TRUE(jval.as_integer() == static_cast<int>(EnumTest::B));
        }

    }
}