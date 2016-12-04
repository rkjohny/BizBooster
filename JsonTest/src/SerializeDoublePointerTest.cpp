/*
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

class DoubolePointerTestBase {
public:
    std::vector<string**> **m_names;

    std::vector<string**>** GetNames() const
    {
        return m_names;
    }

    REGISTER_GETTER_START
    GETTER(DoubolePointerTestBase, std::vector<string**>**, "names", &DoubolePointerTestBase::GetNames)
    REGISTER_GETTER_END
};

class DoublePointerTestDrived {
public:
    int **m_id;
    DoubolePointerTestBase **m_base;

    int** GetId() const
    {
        return m_id;
    }

    DoubolePointerTestBase** GetBase() const
    {
        return m_base;
    }

    REGISTER_GETTER_START
    GETTER(DoublePointerTestDrived, int**, "id", &DoublePointerTestDrived::GetId),
    GETTER(DoublePointerTestDrived, DoubolePointerTestBase**, "base", &DoublePointerTestDrived::GetBase)
    REGISTER_GETTER_END
};

TEST(DoubolePointerTest, TestDoublePointer)
{
    DoubolePointerTestBase ** base = new DoubolePointerTestBase * ();
    *base = new DoubolePointerTestBase();

    std::vector<string**> **names = new std::vector<string**>* ();
    *names = new std::vector<string**>();
    string **name = new string * ();
    *name = new string("first string");
    (*names)->push_back(name);

    name = new string * ();
    *name = new string("second string");
    (*names)->push_back(name);

    (*base)->m_names = names;

    DoublePointerTestDrived **obj = new DoublePointerTestDrived * ();
    *obj = new DoublePointerTestDrived();

    (*obj)->m_id = new int*();
    *((*obj)->m_id) = new int( 100);

    (*obj)->m_base = base;

    json::value jval = Json::ToJson(obj);

    ASSERT_TRUE(jval.is_object());
    ASSERT_EQ(**(*obj)->m_id, jval.at(U("id")).as_integer());
    json::value jbase = jval.at(U("base"));
    ASSERT_TRUE(jbase.is_object());
    json::value jnames = jbase.at(U("names"));
    ASSERT_TRUE(jnames.is_array());

    auto itr = (*(*(*obj)->m_base)->m_names)->begin();
    for (auto &item : jnames.as_array()) {
        ASSERT_TRUE(item.as_string().compare(***itr) == 0);
        ++itr;
    }
}

}
}
