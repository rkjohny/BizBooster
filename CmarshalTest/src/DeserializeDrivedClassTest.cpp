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
#include "Json.h"


// test deserialization of drived class

namespace CmarshalTest {
    namespace JsonTest {
        namespace TestDeserializer {
            using namespace web;
            using namespace std;
            using namespace Cmarshal::Json;

            class BaseClass {
            private:
                double score;
                bool is_valid;

            public:
                BaseClass() : score{24.5678}, is_valid{true} {
                }

                BaseClass(double d, bool b) : score{d}, is_valid{b} {
                }

                virtual ~BaseClass() = default;

                double GetScore() const {
                    return score;
                }

                bool IsValid() const {
                    return is_valid;
                }

                void SetScore(double d) {
                    score = d;
                }

                void SetValid(bool b) {
                    is_valid = b;
                }

                virtual void Clear() {
                    score = 0;
                    is_valid = false;
                }

            REGISTER_GETTER_START
                GETTER(BaseClass, double, "score", &BaseClass::GetScore),
                GETTER(BaseClass, bool, "is_valid", &BaseClass::IsValid)
                REGISTER_GETTER_END

            REGISTER_SETTER_START
                SETTER(BaseClass, double, "score", &BaseClass::SetScore),
                SETTER(BaseClass, bool, "is_valid", &BaseClass::SetValid)
                REGISTER_SETTER_END
            };

            class DrivedClass : public BaseClass {
            private:
                long id;
                string name;
            public:
                DrivedClass() : BaseClass(), id{10L}, name{"name1"} {
                }

                virtual ~DrivedClass() = default;

                long GetId() const {
                    return id;
                }

                string GetName() const {
                    return name;
                }

                void SetId(long i) {
                    id = i;
                }

                void SetName(string s) {
                    name = s;
                }

                void Clear() override {
                    BaseClass::Clear();
                    id = 0;
                    name = "";
                }

            REGISTER_GETTER_INCLUDING_BASE_START(BaseClass)
                GETTER(DrivedClass, long, "id", &DrivedClass::GetId),
                GETTER(DrivedClass, string, "name", &DrivedClass::GetName)
                REGISTER_GETTER_INCLUDING_BASE_END

            REGISTER_SETTER_INCLUDING_BASE_START(BaseClass)
                SETTER(DrivedClass, long, "id", &DrivedClass::SetId),
                SETTER(DrivedClass, string, "name", &DrivedClass::SetName)
                REGISTER_SETTER_INCLUDING_BASE_END
            };

            class DrivedClass2 : public DrivedClass {
            private:
                int code;
            public:
                DrivedClass2() : DrivedClass(), code{200} {
                }

                int GetCode() const {
                    return code;
                }

                void SetCode(int code) {
                    this->code = code;
                }

                void Clear() override {
                    code = 0;
                    DrivedClass::Clear();
                }

            REGISTER_GETTER_INCLUDING_BASE_START(DrivedClass)
                GETTER(DrivedClass2, int, "code", &DrivedClass2::GetCode)
                REGISTER_GETTER_INCLUDING_BASE_END

            REGISTER_SETTER_INCLUDING_BASE_START(DrivedClass)
                SETTER(DrivedClass2, int, "code", &DrivedClass2::SetCode)
                REGISTER_SETTER_INCLUDING_BASE_END
            };

            class DeserializeDrivedClassTest : public ::testing::Test {
            public:
                BaseClass *base;
                DrivedClass *drived;
                DrivedClass2 *drived2;

                void SetUp() override {
                    base = new BaseClass();
                    drived = new DrivedClass();
                    drived2 = new DrivedClass2();
                }

                void TearDown() override {
                    delete base;
                    delete drived;
                    delete drived2;
                }
            };

            TEST_F(DeserializeDrivedClassTest, BaseTest) {
                json::value jvalue = Cmarshal::Json::ToJson(base);

                ASSERT_TRUE(jvalue.is_object());
                ASSERT_DOUBLE_EQ(base->GetScore(), jvalue.at(U("score")).as_double());
                ASSERT_TRUE(base->IsValid() == jvalue.at(U("is_valid")).as_bool());
                cout << jvalue.serialize() << endl;

                base->Clear();
                Cmarshal::Json::FromJson(base, jvalue);

                ASSERT_DOUBLE_EQ(base->GetScore(), jvalue.at(U("score")).as_double());
                ASSERT_TRUE(base->IsValid() == jvalue.at(U("is_valid")).as_bool());
            }

            TEST_F(DeserializeDrivedClassTest, DrivedTest) {
                json::value jvalue = Cmarshal::Json::ToJson(drived);

                ASSERT_TRUE(jvalue.is_object());
                ASSERT_DOUBLE_EQ(drived->GetId(), jvalue.at(U("id")).as_integer());
                ASSERT_TRUE(0 == jvalue.at(U("name")).as_string().compare(drived->GetName()));
                ASSERT_DOUBLE_EQ(drived->GetScore(), jvalue.at(U("score")).as_double());
                ASSERT_TRUE(drived->IsValid() == jvalue.at(U("is_valid")).as_bool());
                cout << jvalue.serialize() << endl;

                drived->Clear();
                Cmarshal::Json::FromJson(drived, jvalue);

                ASSERT_DOUBLE_EQ(drived->GetId(), jvalue.at(U("id")).as_integer());
                ASSERT_TRUE(0 == jvalue.at(U("name")).as_string().compare(drived->GetName()));
                ASSERT_DOUBLE_EQ(drived->GetScore(), jvalue.at(U("score")).as_double());
                ASSERT_TRUE(drived->IsValid() == jvalue.at(U("is_valid")).as_bool());
            }

            TEST_F(DeserializeDrivedClassTest, DrivedTest2) {
                json::value jvalue = Cmarshal::Json::ToJson(drived2);

                ASSERT_TRUE(jvalue.is_object());
                ASSERT_EQ(drived2->GetCode(), jvalue.at(U("code")).as_integer());
                ASSERT_DOUBLE_EQ(drived2->GetId(), jvalue.at(U("id")).as_integer());
                ASSERT_TRUE(0 == jvalue.at(U("name")).as_string().compare(drived2->GetName()));
                ASSERT_DOUBLE_EQ(drived2->GetScore(), jvalue.at(U("score")).as_double());
                ASSERT_TRUE(drived2->IsValid() == jvalue.at(U("is_valid")).as_bool());
                cout << jvalue.serialize() << endl;

                drived2->Clear();
                Cmarshal::Json::FromJson(drived2, jvalue);

                ASSERT_EQ(drived2->GetCode(), jvalue.at(U("code")).as_integer());
                ASSERT_DOUBLE_EQ(drived2->GetId(), jvalue.at(U("id")).as_integer());
                ASSERT_TRUE(0 == jvalue.at(U("name")).as_string().compare(drived2->GetName()));
                ASSERT_DOUBLE_EQ(drived2->GetScore(), jvalue.at(U("score")).as_double());
                ASSERT_TRUE(drived2->IsValid() == jvalue.at(U("is_valid")).as_bool());
            }

        } //namespace TestDeserializer
    } //namespace  CmarshalTest
} //namespace  CmarshalTest