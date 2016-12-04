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

using namespace web;
using namespace std;
using namespace Json;

namespace JsonTest {
namespace TestSerializer {

class BaseClass {
private:
    double score;
    bool is_valid;

public:
    BaseClass() : score{24.5678}, is_valid{true}
    {
    }
    BaseClass(double d, bool b) : score{d}, is_valid{b}
    {
    }

    double GetScore() const
    {
        return score;
    }

    bool IsValid() const
    {
        return is_valid;
    }

    REGISTER_GETTER_START
    GETTER(BaseClass, double, "score", &BaseClass::GetScore),
    GETTER(BaseClass, bool, "is_valid", &BaseClass::IsValid)
    REGISTER_GETTER_END
};

class DrivedClass : public BaseClass {
private:
    long id;
    string name;
public:
    DrivedClass() : BaseClass(), id{10L}, name{"name1"}
    {
    }

    long GetId() const
    {
        return id;
    }

    string GetName() const
    {
        return name;
    }

    REGISTER_GETTER_INCLUDING_BASE_START(BaseClass)
    GETTER(DrivedClass, long, "id", &DrivedClass::GetId),
    GETTER(DrivedClass, string, "name", &DrivedClass::GetName)
    REGISTER_GETTER_INCLUDING_BASE_END
};

class DrivedClass2 : public DrivedClass {
private:
    int code;
public:
    DrivedClass2() : DrivedClass(), code{200}
    {
    }

    int GetCode() const
    {
        return code;
    }

    REGISTER_GETTER_INCLUDING_BASE_START(DrivedClass)
    GETTER(DrivedClass2, int, "code", &DrivedClass2::GetCode)
    REGISTER_GETTER_INCLUDING_BASE_END
};

class SerializeDrivedClassTest : public ::testing::Test {
public:
    BaseClass *base;
    DrivedClass *drived;
    DrivedClass2 *drived2;

    void SetUp() override
    {
        base = new BaseClass();
        drived = new DrivedClass();
        drived2 = new DrivedClass2();
    }

    void TearDown() override
    {
        delete base;
        delete drived;
        delete drived2;
    }
};

TEST_F(SerializeDrivedClassTest, BaseTest)
{
    json::value jvalue = Json::ToJson(base);

    ASSERT_TRUE(jvalue.is_object());
    ASSERT_DOUBLE_EQ(base->GetScore(), jvalue.at(U("score")).as_double());
    ASSERT_TRUE(base->IsValid() == jvalue.at(U("is_valid")).as_bool());
    cout << jvalue.serialize() << endl;
}

TEST_F(SerializeDrivedClassTest, DrivedTest)
{
    json::value jvalue = Json::ToJson(drived);

    ASSERT_TRUE(jvalue.is_object());
    ASSERT_DOUBLE_EQ(drived->GetId(), jvalue.at(U("id")).as_integer());
    ASSERT_TRUE(0 == jvalue.at(U("name")).as_string().compare(drived->GetName()));
    ASSERT_DOUBLE_EQ(drived->GetScore(), jvalue.at(U("score")).as_double());
    ASSERT_TRUE(drived->IsValid() == jvalue.at(U("is_valid")).as_bool());
    cout << jvalue.serialize() << endl;
}

TEST_F(SerializeDrivedClassTest, DrivedTest2)
{
    json::value jvalue = Json::ToJson(drived2);

    ASSERT_TRUE(jvalue.is_object());
    ASSERT_EQ(drived2->GetCode(), jvalue.at(U("code")).as_integer());
    ASSERT_DOUBLE_EQ(drived2->GetId(), jvalue.at(U("id")).as_integer());
    ASSERT_TRUE(0 == jvalue.at(U("name")).as_string().compare(drived2->GetName()));
    ASSERT_DOUBLE_EQ(drived2->GetScore(), jvalue.at(U("score")).as_double());
    ASSERT_TRUE(drived2->IsValid() == jvalue.at(U("is_valid")).as_bool());
    cout << jvalue.serialize() << endl;
}

} //namespace TestSerializer
} //namespace  JsonTest
