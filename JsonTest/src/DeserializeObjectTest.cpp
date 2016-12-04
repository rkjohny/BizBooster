/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of the author (Rezaul Karim)
 *     and is not to be disclosed or used without prior written permission of the author.
 *     This copyrightextends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 */


#include <gtest/gtest.h>
#include <cpprest/json.h>
#include <vector>
#include "Json.h"
#include "Setter.h"
#include "TestSerializableBase.h"

// deserializaion of object test
namespace JsonTest {
namespace TestDeserializer {
using namespace web;

// all getters take value type (without const) arguments

class SimpleClass1 {
public:
    int id;
    std::vector<int> score;

    void SetId(const int id)
    {
        this->id = id;
    }

    void SetScore(std::vector<int> vec)
    {
        this->score = vec;
    }

    void clear()
    {
        score.clear();
        id = 0;
    }

    REGISTER_OWN_SETTER_START
    SETTER(SimpleClass1, const int, "id", &SimpleClass1::SetId),
    SETTER(SimpleClass1, std::vector<int>, "score", &SimpleClass1::SetScore)
    REGISTER_OWN_SETTER_END
};


// all getters take reference (with/without const) type arguments

class SimpleClass2 : public Json::TestSerializableBase {
public:
    int id;
    std::vector<int> score;

    const char* GetClassName() const override
    {
        return "SimpleClass2";
    }

    void SetId(int &id)
    {
        this->id = id;
    }

    void SetScore(const std::vector<int> &vec)
    {
        this->score = vec;
    }

    void clear()
    {
        score.clear();
        id = 0;
    }


    REGISTER_SETTER_START
    BASE_SETTER(Json::TestSerializableBase)
    OWN_SETTER_START
    SETTER(SimpleClass2, int&, "id", &SimpleClass2::SetId),
    SETTER(SimpleClass2, const std::vector<int>&, "score", &SimpleClass2::SetScore)
    OWN_SETTER_END
    REGISTER_SETTER_END
};

// all getters take pointer (without const) type arguments

class SimpleClass3 {
public:
    int *id;
    std::vector<int*> *score;

    void SetId(int *id)
    {
        this->id = (id);
    }

    void SetScore(std::vector<int*> *vec)
    {
        this->score = (vec);
    }

    void clear()
    {
        if (score) {
            for (auto &p : *score)
                delete p;
            delete score;
            score = nullptr;
        }

        if (id) {
            delete id;
            id = nullptr;
        }
    }

    static constexpr auto setters = std::make_tuple(
            Json::Setter<SimpleClass3, int*>(&SimpleClass3::SetId, "id"),
            Json::Setter<SimpleClass3, std::vector<int*> *>(&SimpleClass3::SetScore, "score")
            );
};

// all getters take pointer (with const) type arguments
// this const type is not a real scenario,
// it is just to make sure to be compileable

class SimpleClass4 {
public:
    int *id;
    std::vector<int*> *score;

    void SetId(const int *id)
    {
        this->id = const_cast<int*> (id);
    }

    void SetScore(const std::vector<int*> *vec)
    {
        this->score = const_cast<std::vector<int*> *> (vec);
    }

    void clear()
    {
        if (score) {
            for (auto &p : *score)
                delete p;

            delete score;
            score = nullptr;
        }

        if (id) {
            delete id;
            id = nullptr;
        }
    }

    static constexpr auto setters = std::make_tuple(
            Json::Setter<SimpleClass4, const int*>(&SimpleClass4::SetId, "id"),
            Json::Setter<SimpleClass4, const std::vector<int*> *>(&SimpleClass4::SetScore, "score")
            );
};

// NestedClass holdes a SimpleClass1 object (value type)

class NestedClass {
public:
    SimpleClass1 simpleObject;
    std::vector<SimpleClass1> simpleObjects;

    void SetSimpleObject(const SimpleClass1 &obj)
    {
        simpleObject = obj;
    }

    void SetSimpleObjects(std::vector<SimpleClass1> &objects)
    {
        simpleObjects = objects;
    }

    void Clear()
    {
        simpleObject.clear();
        simpleObjects.clear();
    }

    static constexpr auto setters = std::make_tuple(
            Json::Setter<NestedClass, const SimpleClass1&>(&NestedClass::SetSimpleObject, "object"),
            Json::Setter<NestedClass, std::vector<SimpleClass1> &>(&NestedClass::SetSimpleObjects, "objects")
            );
};

// nested class with pointer type member object

class NestedClass2 {
public:
    SimpleClass1 *simpleObject;
    std::vector<SimpleClass1*> *simpleObjects;

    void SetSimpleObject(SimpleClass1 *obj)
    {
        simpleObject = obj;
    }

    void SetSimpleObjects(std::vector<SimpleClass1*> *objects)
    {
        simpleObjects = objects;
    }

    void clear()
    {
        simpleObject->clear();
        delete simpleObject;

        for (auto p : *simpleObjects) {
            p->clear();
            delete p;
        }

        delete simpleObjects;
    }

    static constexpr auto setters = std::make_tuple(
            Json::Setter<NestedClass2, SimpleClass1*>(&NestedClass2::SetSimpleObject, "object"),
            Json::Setter<NestedClass2, std::vector<SimpleClass1*> *>(&NestedClass2::SetSimpleObjects, "objects")
            );
};

// nested class contains double pointer

class NestedClass3 {
public:
    SimpleClass1 **simpleObject;
    std::vector<SimpleClass1**> **simpleObjects;

    void SetSimpleObject(SimpleClass1 **obj)
    {
        simpleObject = obj;
    }

    void SetSimpleObjects(std::vector<SimpleClass1**> **objects)
    {
        simpleObjects = objects;
    }

    void clear()
    {
        (*simpleObject)->clear();
        delete *simpleObject;
        delete simpleObject;

        for (auto p : **simpleObjects) {
            (*p)->clear();
            delete *p;
            delete p;
        }
        delete *simpleObjects;
        delete simpleObjects;
    }

    static constexpr auto setters = std::make_tuple(
            Json::Setter<NestedClass3, SimpleClass1**>(&NestedClass3::SetSimpleObject, "object"),
            Json::Setter<NestedClass3, std::vector<SimpleClass1**> **>(&NestedClass3::SetSimpleObjects, "objects")
            );
};

void ValidateSimpleObject(SimpleClass1 &simpObj, json::value &jvalue)
{
    ASSERT_EQ(jvalue.at(U("id")).as_integer(), simpObj.id);
    json::array jarray = jvalue.at(U("score")).as_array();
    ASSERT_EQ(jarray.size(), simpObj.score.size());
    auto itr = simpObj.score.begin();

    for (auto &item : jarray) {
        ASSERT_EQ(item.as_integer(), *itr);
        ++itr;
    }
}

void ValidateSimpleObject(SimpleClass2 &simpObj, json::value &jvalue)
{
    ASSERT_EQ(jvalue.at(U("id")).as_integer(), simpObj.id);
    json::array jarray = jvalue.at(U("score")).as_array();
    ASSERT_EQ(jarray.size(), simpObj.score.size());
    auto itr = simpObj.score.begin();

    for (auto &item : jarray) {
        ASSERT_EQ(item.as_integer(), *itr);
        ++itr;
    }
}

void ValidateSimpleObject(SimpleClass3 &simpObj, json::value &jvalue)
{
    ASSERT_EQ(jvalue.at(U("id")).as_integer(), *simpObj.id);
    json::array jarray = jvalue.at(U("score")).as_array();
    ASSERT_EQ(jarray.size(), simpObj.score->size());
    auto itr = simpObj.score->begin();

    for (auto &item : jarray) {
        ASSERT_EQ(item.as_integer(), **itr);
        ++itr;
    }
}

void ValidateSimpleObject(SimpleClass4 &simpObj, json::value &jvalue)
{
    ASSERT_EQ(jvalue.at(U("id")).as_integer(), *simpObj.id);
    json::array jarray = jvalue.at(U("score")).as_array();
    ASSERT_EQ(jarray.size(), simpObj.score->size());
    auto itr = simpObj.score->begin();

    for (auto &item : jarray) {
        ASSERT_EQ(item.as_integer(), **itr);
        ++itr;
    }
}

json::value CreateSimpleObject()
{
    json::value jvalue;
    jvalue[U("id")] = 500;

    json::value jvalarr = json::value::array(3);
    json::array &arr = jvalarr.as_array();
    arr[0] = 10;
    arr[1] = 11;
    arr[2] = 12;
    jvalue[U("score")] = jvalarr;

    return jvalue;
}

json::value CreateNestedObject()
{
    json::value jvalNestObj;

    json::value jvalSimpObj;
    jvalSimpObj[U("id")] = 500;
    json::value jvalarr = json::value::array(3);
    json::array &arr = jvalarr.as_array();
    arr[0] = 10;
    arr[1] = 11;
    arr[2] = 12;
    jvalSimpObj[U("score")] = jvalarr;
    jvalNestObj[U("object")] = jvalSimpObj;

    json::value jvalSimpObjects = json::value::array(2);
    json::array & objectsArr = jvalSimpObjects.as_array();

    jvalSimpObj[U("id")] = 501;
    jvalarr = json::value::array(3);
    json::array &arr2 = jvalarr.as_array();
    arr2[0] = 20;
    arr2[1] = 21;
    arr2[2] = 22;
    jvalSimpObj[U("score")] = jvalarr;
    objectsArr[0] = jvalSimpObj;

    jvalSimpObj[U("id")] = 502;
    jvalarr = json::value::array(3);
    json::array &arr3 = jvalarr.as_array();
    arr3[0] = 30;
    arr3[1] = 31;
    arr3[2] = 32;
    jvalSimpObj[U("score")] = jvalarr;
    objectsArr[1] = jvalSimpObj;
    jvalNestObj[U("objects")] = jvalSimpObjects;

    return jvalNestObj;
}

TEST(DeserializeObjectTest, TestSimpleClass1)
{
    json::value jvalue = CreateSimpleObject();

    SimpleClass1 obj;
    Json::FromJson(obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    obj.clear();
    Json::FromJson(&obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    SimpleClass1 *objPtr = new SimpleClass1();
    Json::FromJson(objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    objPtr = nullptr;
    Json::FromJson(&objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    SimpleClass1 **objPtr2;
    objPtr2 = new SimpleClass1 * ();
    Json::FromJson(objPtr2, jvalue);
    ValidateSimpleObject(**objPtr2, jvalue);
    delete *objPtr2;
    delete objPtr2;
}

TEST(DeserializeObjectTest, TestSimpleClass2)
{
    json::value jvalue = CreateSimpleObject();

    SimpleClass2 obj;
    Json::FromJson(obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    obj.clear();
    Json::FromJson(&obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    SimpleClass2 *objPtr = new SimpleClass2();
    Json::FromJson(objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    objPtr = nullptr;
    Json::FromJson(&objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    SimpleClass2 **objPtr2;
    objPtr2 = new SimpleClass2 * ();
    Json::FromJson(objPtr2, jvalue);
    ValidateSimpleObject(**objPtr2, jvalue);
    delete *objPtr2;
    delete objPtr2;
}

TEST(DeserializeObjectTest, TestSimpleClass3)
{
    json::value jvalue = CreateSimpleObject();

    SimpleClass3 obj;
    Json::FromJson(obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    obj.clear();
    Json::FromJson(&obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    SimpleClass3 *objPtr = new SimpleClass3();
    Json::FromJson(objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    objPtr = nullptr;
    Json::FromJson(&objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    SimpleClass3 **objPtr2;
    objPtr2 = new SimpleClass3 * ();
    Json::FromJson(objPtr2, jvalue);
    ValidateSimpleObject(**objPtr2, jvalue);
    delete *objPtr2;
    delete objPtr2;
}

TEST(DeserializeObjectTest, TestSimpleClass4)
{
    json::value jvalue = CreateSimpleObject();

    SimpleClass4 obj;
    Json::FromJson(obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    obj.clear();
    Json::FromJson(&obj, jvalue);
    ValidateSimpleObject(obj, jvalue);

    SimpleClass4 *objPtr = new SimpleClass4();
    Json::FromJson(objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    objPtr = nullptr;
    Json::FromJson(&objPtr, jvalue);
    ValidateSimpleObject(*objPtr, jvalue);
    delete objPtr;

    SimpleClass4 **objPtr2;
    objPtr2 = new SimpleClass4 * ();
    Json::FromJson(objPtr2, jvalue);
    ValidateSimpleObject(**objPtr2, jvalue);
    delete *objPtr2;
    delete objPtr2;
}

TEST(DeserializeObjectTest, NestedClassTest)
{
    json::value jvalNestObj = CreateNestedObject();

    NestedClass nestObject;
    Json::FromJson(nestObject, jvalNestObj);

    json::value jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(nestObject.simpleObject, jvalSimpObj);

    json::array jarray = jvalNestObj.at(U("objects")).as_array();
    auto itr = nestObject.simpleObjects.begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(*itr, item);
        ++itr;
    }

    nestObject.Clear();
    Json::FromJson(&nestObject, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(nestObject.simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = nestObject.simpleObjects.begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(*itr, item);
        ++itr;
    }

    NestedClass *objptr = new NestedClass;
    Json::FromJson(objptr, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(objptr->simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = objptr->simpleObjects.begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(*itr, item);
        ++itr;
    }

    delete objptr;
    objptr = nullptr;
    Json::FromJson(&objptr, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(objptr->simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = objptr->simpleObjects.begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(*itr, item);
        ++itr;
    }

    delete objptr;

    NestedClass **objPtr2 = new NestedClass * ();
    Json::FromJson(objPtr2, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject((*objPtr2)->simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = (*objPtr2)->simpleObjects.begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(*itr, item);
        ++itr;
    }
}

TEST(DeserializeObjectTest, NestedClassTest2)
{
    json::value jvalNestObj = CreateNestedObject();

    NestedClass2 nestObject;
    Json::FromJson(nestObject, jvalNestObj);

    json::value jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(*nestObject.simpleObject, jvalSimpObj);

    json::array jarray = jvalNestObj.at(U("objects")).as_array();
    auto itr = nestObject.simpleObjects->begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(**itr, item);
        ++itr;
    }

    nestObject.clear();
    Json::FromJson(&nestObject, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(*nestObject.simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = nestObject.simpleObjects->begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(**itr, item);
        ++itr;
    }

    NestedClass2 *objPtr = new NestedClass2();
    Json::FromJson(objPtr, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(*objPtr->simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = objPtr->simpleObjects->begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(**itr, item);
        ++itr;
    }

    delete objPtr;

    objPtr = nullptr;
    Json::FromJson(&objPtr, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(*objPtr->simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = objPtr->simpleObjects->begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(**itr, item);
        ++itr;
    }
    delete objPtr;

    NestedClass2 **objPtr2 = new NestedClass2 * ();
    Json::FromJson(objPtr2, jvalNestObj);

    jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(*(*objPtr2)->simpleObject, jvalSimpObj);

    jarray = jvalNestObj.at(U("objects")).as_array();
    itr = (*objPtr2)->simpleObjects->begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(**itr, item);
        ++itr;
    }
}

TEST(DeserializeObjectTest, NestedClassTest3)
{
    json::value jvalNestObj = CreateNestedObject();

    NestedClass3 nestObject;
    Json::FromJson(nestObject, jvalNestObj);

    json::value jvalSimpObj = jvalNestObj.at(U("object"));
    ValidateSimpleObject(**(nestObject.simpleObject), jvalSimpObj);

    json::array jarray = jvalNestObj.at(U("objects")).as_array();
    auto itr = (*(nestObject.simpleObjects))->begin();

    for (auto &item : jarray) {
        ValidateSimpleObject(***itr, item);
        ++itr;
    }
}

} //namespace TestDeserializer
} // namespace JsonTest
