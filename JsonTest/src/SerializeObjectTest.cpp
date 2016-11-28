/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */
#include <iostream>

#include <gtest/gtest.h>
#include <cpprest/json.h>
#include <vector>
#include <string>
#include <tuple>
#include "Getter.h"
#include "Json.h"

using namespace std;
using namespace Json;


namespace JsonTest {
namespace TestSerializer {

class SimpleClass {
private:
    long m_id;
    string m_name;
    string *m_address;
    int *m_age;
    double m_score;
    char *m_city;
    bool m_isValid;

    vector<int> m_vecInt;
    vector<string> m_vecString;
    vector<string*> *m_vecStringPtr;
    vector<double> *m_vecDouble;
    vector<char*> m_vecChar;
    vector<long*> m_vecLong;

public:

    SimpleClass()
    {
        m_id = 10;
        m_name = "rezaul";
        m_address = new string("Badda, Dhaka, Bangladesh");
        m_age = new int( 37);
        m_score = 15.3;
        m_city = new char( 10);
        strcpy(m_city, "Dhaka");
        m_isValid = true;

        m_vecInt.push_back(10);
        m_vecInt.push_back(11);
        m_vecInt.push_back(12);

        m_vecString.push_back("first string");
        m_vecString.push_back("second string");
        m_vecString.push_back("third string");

        m_vecStringPtr = new vector<string*>();
        m_vecStringPtr->push_back(new string("first string pointer"));
        m_vecStringPtr->push_back(new string("second string pointer"));
        m_vecStringPtr->push_back(new string("third string pointer"));

        m_vecDouble = new vector<double>();
        m_vecDouble->push_back(20.50);
        m_vecDouble->push_back(20.51);
        m_vecDouble->push_back(20.52);

        char *p = new char[100];
        strcpy(p, "this is first string");
        m_vecChar.push_back(p);

        p = new char[100];
        strcpy(p, "this is second string");
        m_vecChar.push_back(p);

        p = new char[100];
        strcpy(p, "this is third string");
        m_vecChar.push_back(p);

        m_vecLong.push_back(new long( 20L));
        m_vecLong.push_back(new long( 21L));
        m_vecLong.push_back(new long( 22L));
    }

    virtual ~SimpleClass()
    {
        delete m_address;
        delete m_age;
        delete m_city;

        for (auto p : *m_vecStringPtr) {
            delete p;
        }
        delete m_vecStringPtr;

        delete m_vecDouble;

        for (auto p : m_vecLong) {
            delete p;
        }

        for (auto p : m_vecChar) {
            delete p;
        }
    }

    long GetId() const
    {
        return m_id;
    }

    const string& GetName() const
    {
        return m_name;
    }

    const string* GetAddress() const
    {
        return m_address;
    }

    const int* GetAge() const
    {
        return m_age;
    }

    double GetScore() const
    {
        return m_score;
    }

    const char* GetCity() const
    {
        return m_city;
    }

    bool IsValid() const
    {
        return m_isValid;
    }

    const vector<int>& GetVecInt() const
    {
        return m_vecInt;
    }

    const vector<string>& GetVecString() const
    {
        return m_vecString;
    }

    const vector<string*>* GetVecStringPtr() const
    {
        return m_vecStringPtr;
    }

    const vector<double>* GetVecDouble() const
    {
        return m_vecDouble;
    }

    const vector<char*>& GetVecChar() const
    {
        return m_vecChar;
    }

    const vector<long*>& GetVecLong() const
    {
        return m_vecLong;
    }

    static constexpr auto getters = std::make_tuple(
            Json::Getter<SimpleClass, long>(&SimpleClass::GetId, "id"),
            Json::Getter<SimpleClass, const string&>(&SimpleClass::GetName, "name"),
            Json::Getter<SimpleClass, const string*>(&SimpleClass::GetAddress, "address"),
            Json::Getter<SimpleClass, const int*>(&SimpleClass::GetAge, "age"),
            Json::Getter<SimpleClass, double>(&SimpleClass::GetScore, "score"),
            Json::Getter<SimpleClass, const char*>(&SimpleClass::GetCity, "city"),
            Json::Getter<SimpleClass, bool>(&SimpleClass::IsValid, "is_valid"),
            Json::Getter<SimpleClass, const vector<int>&>(&SimpleClass::GetVecInt, "int_vector"),
            Json::Getter<SimpleClass, const vector<string>&>(&SimpleClass::GetVecString, "str_vector"),
            Json::Getter<SimpleClass, const vector<string*>*>(&SimpleClass::GetVecStringPtr, "str_vector_ptr"),
            Json::Getter<SimpleClass, const vector<double>*>(&SimpleClass::GetVecDouble, "double_vector"),
            Json::Getter<SimpleClass, const vector<char*>&>(&SimpleClass::GetVecChar, "char_vector"),
            Json::Getter<SimpleClass, const vector<long*>&>(&SimpleClass::GetVecLong, "long_vector")
            );
};

class SerializeSimpleObjectTest : public ::testing::Test {
public:
    SerializeSimpleObjectTest() = default;
    ~SerializeSimpleObjectTest() = default;

    void SetUp() override
    {
    }

    void TearDown() override
    {
    }

    static void Validate(json::value &jvalue, SimpleClass &obj)
    {
        json::value jvalVect;

        ASSERT_TRUE(jvalue.is_object());
        ASSERT_TRUE(jvalue.at(U("id")).is_number());
        ASSERT_TRUE(jvalue.at(U("id")).as_number().is_int64());
        ASSERT_TRUE(jvalue.at(U("id")).as_number().to_int64() == obj.GetId());
        ASSERT_TRUE(jvalue.at(U("id")).as_integer() == obj.GetId());


        ASSERT_TRUE(jvalue.at(U("name")).as_string().compare(obj.GetName()) == 0);
        ASSERT_TRUE(jvalue.at(U("address")).as_string().compare(*obj.GetAddress()) == 0);
        ASSERT_TRUE(jvalue.at(U("age")).as_integer() == *obj.GetAge());
        ASSERT_DOUBLE_EQ(jvalue.at(U("score")).as_double(), obj.GetScore());
        ASSERT_TRUE(jvalue.at(U("city")).as_string().compare(U(obj.GetCity())) == 0);
        ASSERT_TRUE(jvalue.at(U("is_valid")).as_bool() == obj.IsValid());

        jvalVect = jvalue.at(U("int_vector"));
        ASSERT_TRUE(jvalVect.is_array());
        ASSERT_TRUE(jvalVect.as_array().size() == obj.GetVecInt().size());
        auto itrIntVec = obj.GetVecInt().begin();
        for (auto &arrItem : jvalVect.as_array()) {
            ASSERT_EQ(arrItem.as_integer(), *itrIntVec);
            ++itrIntVec;
        }

        jvalVect = jvalue.at(U("str_vector"));
        ASSERT_TRUE(jvalVect.is_array());
        ASSERT_TRUE(jvalVect.as_array().size() == obj.GetVecString().size());
        auto itrStrVec = obj.GetVecString().begin();
        for (auto &arrItem : jvalVect.as_array()) {
            ASSERT_EQ(arrItem.as_string().compare(*itrStrVec), 0);
            ++itrStrVec;
        }

        jvalVect = jvalue.at(U("str_vector_ptr"));
        ASSERT_TRUE(jvalVect.is_array());
        ASSERT_TRUE(jvalVect.as_array().size() == obj.GetVecStringPtr()->size());
        auto itrStrVecPtr = obj.GetVecStringPtr()->begin();
        for (auto &arrItem : jvalVect.as_array()) {
            ASSERT_EQ(arrItem.as_string().compare(**itrStrVecPtr), 0);
            ++itrStrVecPtr;
        }

        jvalVect = jvalue.at(U("double_vector"));
        ASSERT_TRUE(jvalVect.is_array());
        ASSERT_TRUE(jvalVect.as_array().size() == obj.GetVecDouble()->size());
        auto itrDoubleVec = obj.GetVecDouble()->begin();
        for (auto &arrItem : jvalVect.as_array()) {
            ASSERT_DOUBLE_EQ(arrItem.as_double(), *itrDoubleVec);
            ++itrDoubleVec;
        }

        jvalVect = jvalue.at(U("char_vector"));
        ASSERT_TRUE(jvalVect.is_array());
        ASSERT_TRUE(jvalVect.as_array().size() == obj.GetVecChar().size());
        auto itrCharVec = obj.GetVecChar().begin();
        for (auto &arrItem : jvalVect.as_array()) {
            ASSERT_EQ(arrItem.as_string().compare(U(*itrCharVec)), 0);
            ++itrCharVec;
        }

        jvalVect = jvalue.at(U("long_vector"));
        ASSERT_TRUE(jvalVect.is_array());
        ASSERT_TRUE(jvalVect.as_array().size() == obj.GetVecLong().size());
        auto itrLongVec = obj.GetVecLong().begin();
        for (auto &arrItem : jvalVect.as_array()) {
            ASSERT_EQ(arrItem.as_integer(), **itrLongVec);
            ++itrLongVec;
        }
    }
};

TEST_F(SerializeSimpleObjectTest, SimpleClassTest)
{
    SimpleClass obj;
    json::value jvalue;

    jvalue = Json::ToJson(SimpleClass());
    Validate(jvalue, obj);
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson(std::move(obj));
    Validate(jvalue, obj);
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson(obj);
    Validate(jvalue, obj);
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson(&obj);
    Validate(jvalue, obj);
    cout << jvalue.serialize() << endl;
}

} // namespace TestSerializer
} // namespace JsonTest
