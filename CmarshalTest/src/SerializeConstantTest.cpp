
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
#include <vector>
#include <string>
#include "Json.h"


//deserializing an object containing constant data

namespace CmarshalTest {
    namespace JsonTest {
        namespace TestSerializer {
            using namespace web;
            using namespace std;
            using namespace Cmarshal::Json;

            class SerializeConstantTest : public ::testing::Test {
            public:
                SerializeConstantTest() = default;

                virtual ~SerializeConstantTest() = default;

                std::vector<const double *> *m_scores;
                std::vector<const std::string *> *m_emails;
                std::vector<const char *> m_cities;

                void SetUp() override {
                    m_scores = new vector<const double *>;
                    m_scores->push_back(new double(9.9));
                    m_scores->push_back(new double(10.01));
                    m_scores->push_back(new double(10.1));
                    m_scores->push_back(new double(10.4));
                    m_scores->push_back(new double(10.5));


                    m_emails = new std::vector<const std::string *>();
                    m_emails->push_back(new string("first string pointer"));
                    m_emails->push_back(new string("second string pointer"));
                    m_emails->push_back(new string("third string pointer"));

                    char *p = new char[100];
                    strcpy(p, "this is first string pointer");
                    m_cities.push_back(p);

                    p = new char[100];
                    strcpy(p, "this is second string pointer");
                    m_cities.push_back(p);

                    p = new char[100];
                    strcpy(p, "this is third string pointer");
                    m_cities.push_back(p);
                }

                void TearDown() override {
                    for (auto p : *m_scores) {
                        delete p;
                    }
                    delete m_scores;

                    for (auto p : *m_emails) {
                        delete p;
                    }
                    delete m_emails;

                    for (auto p : m_cities) {
                        delete p;
                    }
                }
            };

            TEST_F(SerializeConstantTest, TestInt) {
                json::value jvalue;
                const std::vector<int> vecInt({1, 2, 3});

                jvalue = Cmarshal::Json::ToJson(std::move(vecInt));
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecInt.size());
                auto itr = vecInt.begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(*itr, arrItem.as_integer());
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(vecInt);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecInt.size());
                itr = vecInt.begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(*itr, arrItem.as_integer());
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(&vecInt);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecInt.size());
                itr = vecInt.begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(*itr, arrItem.as_integer());
                    ++itr;
                }
            }

            TEST_F(SerializeConstantTest, TestScore) {
                json::value jvalue;
                const vector<const double *> *const vecPtr = m_scores;

                jvalue = Cmarshal::Json::ToJson(std::move(*vecPtr));
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                auto itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_DOUBLE_EQ(arrItem.as_double(), **itr);
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(*vecPtr);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_DOUBLE_EQ(arrItem.as_double(), **itr);
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(vecPtr);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_DOUBLE_EQ(arrItem.as_double(), **itr);
                    ++itr;
                }
            }

            TEST_F(SerializeConstantTest, TestEmails) {
                json::value jvalue;
                const vector<const string *> *const vecPtr = m_emails;

                jvalue = Cmarshal::Json::ToJson(vector<const string *>(*vecPtr));
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                auto itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(std::move(*vecPtr));
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(*vecPtr);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(vecPtr);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
                    ++itr;
                }
            }

            TEST_F(SerializeConstantTest, TestCeties) {
                json::value jvalue;
                const vector<const char *> *const vecPtr = &m_cities;

                jvalue = Cmarshal::Json::ToJson(std::vector<const char *>(*vecPtr));
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                auto itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(std::move(*vecPtr));
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(*vecPtr);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
                    ++itr;
                }

                jvalue = Cmarshal::Json::ToJson(vecPtr);
                ASSERT_TRUE(jvalue.is_array());
                ASSERT_TRUE(jvalue.as_array().size() == vecPtr->size());
                itr = vecPtr->begin();
                for (auto &arrItem : jvalue.as_array()) {
                    ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
                    ++itr;
                }
            }

        } // namespace SerializingTest
    } // namespace TestJson
} // namespace CmarshalTest