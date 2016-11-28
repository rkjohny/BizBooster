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
#include <vector>
#include <string>
#include "Json.h"

using namespace web;
using namespace std;
using namespace Json;

namespace JsonTest {
namespace TestSerializer {

class SerializeVectorTest : public ::testing::Test {
public:
    SerializeVectorTest() = default;
    virtual ~SerializeVectorTest() = default;

    std::vector<double*> *m_scores;
    std::vector<std::string> *m_names;
    std::vector<std::string*> *m_emails;
    std::vector<char*> m_cities;

    void SetUp() override
    {
        m_scores = new vector<double*>;
        m_scores->push_back(new double( 9.9));
        m_scores->push_back(new double( 10.01));
        m_scores->push_back(new double( 10.1));
        m_scores->push_back(new double( 10.4));
        m_scores->push_back(new double( 10.5));

        m_names = new std::vector<std::string>();
        m_names->push_back(string("first string"));
        m_names->push_back(string("second string"));
        m_names->push_back(string("third string"));


        m_emails = new std::vector<std::string*>();
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

    void TearDown() override
    {
        for (auto p : *m_scores) {
            delete p;
        }
        delete m_scores;

        delete m_names;

        for (auto p : *m_emails) {
            delete p;
        }
        delete m_emails;

        for (auto p : m_cities) {
            delete p;
        }
    }
};

TEST_F(SerializeVectorTest, TestInt)
{
    json::value jvalue;
    int val = 0;
    std::vector<int> vecInt;

    vecInt.push_back(1);
    vecInt.push_back(2);
    vecInt.push_back(3);

    jvalue = Json::ToJson(vector<int>({1, 2, 3}));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == 3);
    val = 1;
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(val++, arrItem.as_integer());
    }

    jvalue = Json::ToJson(std::move(vecInt));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == vecInt.size());
    auto itr1 = vecInt.begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(*itr1, arrItem.as_integer());
        ++itr1;
    }

    jvalue = Json::ToJson(vecInt);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == vecInt.size());
    auto itr2 = vecInt.begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(*itr2, arrItem.as_integer());
        ++itr2;
    }

    jvalue = Json::ToJson(&vecInt);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == vecInt.size());
    auto itr3 = vecInt.begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(*itr3, arrItem.as_integer());
        ++itr3;
    }
}

TEST_F(SerializeVectorTest, TestScore)
{
    json::value jvalue;

    jvalue = Json::ToJson(std::move(*m_scores));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_scores->size());
    auto itr = m_scores->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_DOUBLE_EQ(arrItem.as_double(), **itr);
        ++itr;
    }

    jvalue = Json::ToJson(*m_scores);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_scores->size());
    itr = m_scores->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_DOUBLE_EQ(arrItem.as_double(), **itr);
        ++itr;
    }

    jvalue = Json::ToJson(m_scores);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_scores->size());
    itr = m_scores->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_DOUBLE_EQ(arrItem.as_double(), **itr);
        ++itr;
    }
}

TEST_F(SerializeVectorTest, TestNames)
{
    json::value jvalue;

    jvalue = Json::ToJson(vector<string>(*m_names));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_names->size());
    auto itr = m_names->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (*itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(std::move(*m_names));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_names->size());
    itr = m_names->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (*itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(*m_names);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_names->size());
    itr = m_names->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (*itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(m_names);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_names->size());
    itr = m_names->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (*itr).compare(arrItem.as_string()));
        ++itr;
    }
}

TEST_F(SerializeVectorTest, TestEmails)
{
    json::value jvalue;

    jvalue = Json::ToJson(vector<string*>(*m_emails));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_emails->size());
    auto itr = m_emails->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(std::move(*m_emails));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_emails->size());
    itr = m_emails->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(*m_emails);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_emails->size());
    itr = m_emails->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(m_emails);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_emails->size());
    itr = m_emails->begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, (**itr).compare(arrItem.as_string()));
        ++itr;
    }
}

TEST_F(SerializeVectorTest, TestCities)
{
    json::value jvalue;

    jvalue = Json::ToJson(std::vector<char*>(m_cities));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_cities.size());
    auto itr = m_cities.begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(std::move(m_cities));
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_cities.size());
    itr = m_cities.begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(m_cities);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_cities.size());
    itr = m_cities.begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
        ++itr;
    }

    jvalue = Json::ToJson(&m_cities);
    ASSERT_TRUE(jvalue.is_array());
    ASSERT_TRUE(jvalue.as_array().size() == m_cities.size());
    itr = m_cities.begin();
    for (auto &arrItem : jvalue.as_array()) {
        ASSERT_EQ(0, std::string(*itr).compare(arrItem.as_string()));
        ++itr;
    }
}

} // namespace SerializingTest
} // namespace TestJson
