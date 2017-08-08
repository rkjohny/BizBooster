/*
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of the author (Rezaul Karim)
 *     and is not to be disclosed or used without prior written permission of the author.
 *     This copyrightextends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 */

#include <gtest/gtest.h>
#include <cpprest/json.h>
#include <string>

#include "Json.h"


// deserialization of pod test

namespace CmarshalTest {
    namespace JsonTest {
        namespace TestDeserializer {

            using namespace std;
            using namespace Cmarshal::Json;
            using namespace web;

            class POD1 {
            public:
                long m_id;
                string m_name;
                string *m_address;
                int *m_age;
                double m_score;
                const char *m_city;
                bool m_isValid;
                string **m_emails;

                void SetId(long id) {
                    m_id = id;
                }

                void SetName(const string &n) {
                    m_name = n;
                }

                void SetAddr(const string *a) {
                    m_address = const_cast<string *> (a);
                }

                void SetAge(int *a) {
                    m_age = a;
                }

                void SetScore(double s) {
                    m_score = s;
                }

                void SetCity(const char *c) {
                    m_city = c;
                }

                void SetValid(bool b) {
                    m_isValid = b;
                }

                void SetEmails(string **e) {
                    m_emails = e;
                }

            REGISTER_SETTER_START
                SETTER(POD1, long, "id", &POD1::SetId),
                SETTER(POD1, const string&, "name", &POD1::SetName),
                SETTER(POD1, const string*, "address", &POD1::SetAddr),
                SETTER(POD1, int*, "age", &POD1::SetAge),
                SETTER(POD1, double, "score", &POD1::SetScore),
                SETTER(POD1, const char*, "city", &POD1::SetCity),
                SETTER(POD1, bool, "valid", &POD1::SetValid),
                SETTER(POD1, std::string**, "emails", &POD1::SetEmails)
                REGISTER_SETTER_END
            };

            json::value CreatePOD1() {
                json::value jvalue;

                jvalue[U("id")] = json::value(100);
                jvalue[U("name")] = json::value(U("Rezaul Karim"));
                jvalue[U("address")] = json::value(U("Uttar Badda, Dhaka-2012, Bangladesh"));
                jvalue[U("age")] = json::value(37);
                jvalue[U("score")] = json::value(85.10);
                jvalue[U("city")] = json::value(U("dhaka city"));
                jvalue[U("valid")] = json::value(true);
                jvalue[U("emails")] = json::value("reza1@domain1.com, reza2@domail2.com, reza3@domain3.com");

                return jvalue;
            }

            void VerifyPOD(const POD1 &obj, const json::value &jvalue) {
                ASSERT_EQ(obj.m_id, jvalue.at(U("id")).as_number().to_int64());
                ASSERT_TRUE(jvalue.at(U("name")).as_string().compare(obj.m_name) == 0);
                ASSERT_TRUE(jvalue.at(U("address")).as_string().compare(*obj.m_address) == 0);
                ASSERT_EQ(*obj.m_age, jvalue.at(U("age")).as_integer());
                ASSERT_DOUBLE_EQ(obj.m_score, jvalue.at(U("score")).as_double());
                ASSERT_TRUE(jvalue.at(U("city")).as_string().compare(obj.m_city) == 0);
                ASSERT_EQ(obj.m_isValid, jvalue.at(U("valid")).as_bool());
                ASSERT_TRUE(jvalue.at(U("emails")).as_string().compare(**obj.m_emails) == 0);
            }

            TEST(POD1, TestPod) {
                json::value jval = CreatePOD1();
                POD1 obj;
                Cmarshal::Json::FromJson(obj, jval);
                VerifyPOD(obj, jval);
            }

        } //namespace TestDeserializer
    } // namespace CmarshalTest
} // namespace CmarshalTest