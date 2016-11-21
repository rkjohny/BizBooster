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
#include "TestSerializableBase.h"

using namespace web;
using namespace std;
using namespace Json;

// deserializing an object containing another object
namespace JsonTest
{
namespace TestSerializer
{


class ClassA
{
private:
    int id;
    string name;

public:
    ClassA() = default;

    ClassA( const ClassA &a ) : id {a.id}, name {a.name} {}

    ClassA( ClassA &&a ) : id {a.id}, name {std::move( a.name )} {}

    ClassA( int id, string name ): id {id}, name {std::move( name )} {}

    ClassA& operator = ( const ClassA &a )
    {
        id = a.id;
        name = a.name;
        return *this;
    }

    ClassA& operator = ( ClassA && a )
    {
        //*this = std::move(a);
        id = a.id;
        name = std::move( a.name );
        return *this;
    }

    ~ClassA() = default;

    int GetId() const
    {
        return id;
    }
    const string &GetName() const
    {
        return name;
    }

    REGISTER_GETTER_START
    GETTER( ClassA, int, "id", &ClassA::GetId ),
            GETTER( ClassA, const string&, "name", &ClassA::GetName )
            REGISTER_GETTER_END
};

class ClassB : public Json::TestSerializableBase
{
private:
    ClassA m_obj;
    ClassA *m_objPtr;
    std::vector<ClassA> m_vecObj;
    std::vector<ClassA*> *m_vecObjPtr;

public:
    ClassB( ClassA &a, ClassA *p, std::vector<ClassA> &vect, std::vector<ClassA*>* vectPtr )
    {
        m_obj = a;
        m_objPtr = p;
        m_vecObj = std::move( vect );
        m_vecObjPtr = vectPtr;
    }

    ~ClassB()
    {
        if ( m_objPtr )
        {
            delete m_objPtr;
        }

        if ( m_vecObjPtr )
        {
            for ( auto p : *m_vecObjPtr )
            {
                if ( p )
                {
                    delete p;
                }
            }
            delete m_vecObjPtr;
        }
    }

    const char * GetClassName() const override
    {
        return "ClassB";
    }

    const ClassA& GetObject() const
    {
        return m_obj;
    }

    const ClassA* GetObjectPtr() const
    {
        return m_objPtr;
    }

    const vector<ClassA>& GetVector() const
    {
        return m_vecObj;
    }

    const vector<ClassA*>* GetVectorPtr() const
    {
        return m_vecObjPtr;
    }

    const ClassA* GetNullPtrObject() const
    {
        return nullptr;
    }

    const int* GetNullPtrInt() const
    {
        return nullptr;
    }


    REGISTER_ALL_GETTER_START
    BASE_GETTER( TestSerializableBase )
    OWN_GETTER_START
    GETTER( ClassB, const ClassA&, "object", &ClassB::GetObject ),
            GETTER( ClassB, const ClassA*, "object_ptr", &ClassB::GetObjectPtr ),
            GETTER( ClassB, const vector<ClassA>&, "vector", &ClassB::GetVector ),
            GETTER( ClassB, const vector<ClassA*>*, "vector_ptr", &ClassB::GetVectorPtr ),
            GETTER( ClassB, const ClassA*, "null_objec_ptr", &ClassB::GetNullPtrObject ),
            GETTER( ClassB, const int*, "null_int_ptr", &ClassB::GetNullPtrInt )
            OWN_GETTER_END
            REGISTER_ALL_GETER_END

            //    REGISTER_GETER_START
            //    GETTER (ClassB, const ClassA&, "object", &ClassB::GetObject),
            //    GETTER (ClassB, const ClassA*, "object_ptr", &ClassB::GetObjectPtr),
            //    GETTER (ClassB, const vector<ClassA>&, "vector", &ClassB::GetVector),
            //    GETTER (ClassB, const vector<ClassA*>*, "vector_ptr", &ClassB::GetVectorPtr)
            //    REGISTER_GETTER_END
};

class ClassC : public TestSerializableBase
{
private:
    ClassB *objectB;

public:
    ClassC( ClassB *p ) : objectB {p} {}
    ~ClassC()
    {
        if ( objectB )
        {
            delete objectB;
        }
    }

    const char * GetClassName() const override
    {
        return "ClassC";
    }

    const ClassB* GetObject() const
    {
        return objectB;
    }

    REGISTER_GETTER_START
    GETTER( ClassC, const ClassB*, "object", &ClassC::GetObject )
    REGISTER_GETTER_END
};

class SerializeNestedObjectTest : public ::testing::Test
{
public:
    ClassA* objectA;
    ClassB* objectB;
    ClassC* objectC;

    void SetUp() override
    {
        objectA = new ClassA( 1, "object1" );

        ClassA &&a = ClassA( 2, "object2" );
        ClassA *ap = new ClassA( 3, "object3" );
        vector<ClassA> &&vec = vector<ClassA>();
        vec.push_back( ClassA( 4, "object4" ) );
        vec.push_back( ClassA( 5, "object5" ) );
        vec.push_back( ClassA( 6, "object6" ) );
        vector<ClassA*> *vecp = new vector<ClassA*>();
        vecp->push_back( new ClassA( 7, "object7" ) );
        vecp->push_back( new ClassA( 8, "object8" ) );
        vecp->push_back( new ClassA( 9, "object9" ) );
        objectB = new ClassB( a, ap, vec, vecp );


        ClassA &&ac = ClassA( 10, "object10" );
        ClassA *acp = new ClassA( 11, "object11" );
        vector<ClassA> &&vecc = vector<ClassA>();
        vecc.push_back( ClassA( 12, "object12" ) );
        vecc.push_back( ClassA( 13, "object13" ) );
        vecc.push_back( ClassA( 14, "object14" ) );
        vector<ClassA*> *veccp = new vector<ClassA*>();
        veccp->push_back( new ClassA( 15, "object15" ) );
        veccp->push_back( new ClassA( 16, "object16" ) );
        veccp->push_back( new ClassA( 17, "object17" ) );
        objectC = new ClassC( new ClassB( ac, acp, vecc, veccp ) );
    }

    void TearDown() override
    {
        delete objectA;
        delete objectB;
        delete objectC;
    }

    static void VerifyClassA( const ClassA &obj, const json::value &jvalue )
    {
        ASSERT_TRUE( jvalue.is_object() );
        ASSERT_EQ( obj.GetId(), jvalue.at( U( "id" ) ).as_integer() );
        ASSERT_EQ( 0, jvalue.at( U( "name" ) ).as_string().compare( obj.GetName() ) );
    }

    static void VerifyClassB( const ClassB &obj, const json::value &jvalue )
    {
        ASSERT_TRUE( jvalue.is_object() );
        VerifyClassA( obj.GetObject(), jvalue.at( U( "object" ) ) );
        VerifyClassA( *obj.GetObjectPtr(), jvalue.at( U( "object_ptr" ) ) );

        const json::value &vec = jvalue.at( U( "vector" ) );
        ASSERT_TRUE( vec.is_array() );
        ASSERT_TRUE( vec.as_array().size() == obj.GetVector().size() );

        auto itr = obj.GetVector().begin();
        for ( auto& arrItem : vec.as_array() )
        {
            VerifyClassA( *itr, arrItem );
            ++itr;
        }

        const json::value &vecp = jvalue.at( U( "vector_ptr" ) );
        ASSERT_TRUE( vecp.is_array() );
        ASSERT_TRUE( vecp.as_array().size() == obj.GetVectorPtr()->size() );

        auto itrp = obj.GetVectorPtr()->begin();
        for ( auto& arrItem : vecp.as_array() )
        {
            VerifyClassA( **itrp, arrItem );
            ++itrp;
        }
    }

    static void VerifyClassC( const ClassC &obj, const json::value &jvalue )
    {
        ASSERT_TRUE( jvalue.is_object() );
        VerifyClassB( *obj.GetObject(), jvalue.at( U( "object" ) ) );
    }
};

TEST_F( SerializeNestedObjectTest, SimpleObject )
{
    json::value jvalue;

    jvalue = Json::ToJson( std::move( *objectA ) );
    VerifyClassA( *objectA, jvalue );
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson( *objectA );
    VerifyClassA( *objectA, jvalue );
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson( objectA );
    VerifyClassA( *objectA, jvalue );
    cout << jvalue.serialize() << endl;
}

TEST_F( SerializeNestedObjectTest, NestedObject )
{
    json::value jvalue;

    jvalue = Json::ToJson( std::move( *objectB ) );
    VerifyClassB( *objectB, jvalue );
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson( *objectB );
    VerifyClassB( *objectB, jvalue );
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson( objectB );
    VerifyClassB( *objectB, jvalue );
    cout << jvalue.serialize() << endl;
}

TEST_F( SerializeNestedObjectTest, NestedObject2 )
{
    json::value jvalue;

    jvalue = Json::ToJson( std::move( *objectC ) );
    VerifyClassC( *objectC, jvalue );
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson( *objectC );
    VerifyClassC( *objectC, jvalue );
    cout << jvalue.serialize() << endl;

    jvalue = Json::ToJson( objectC );
    VerifyClassC( *objectC, jvalue );
    cout << jvalue.serialize() << endl;
}

} //namespace TestSerializer
} //namespave JsonTest
