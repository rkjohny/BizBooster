/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of the author (Rezaul Karim)
 *     and is not to be disclosed or used without prior written permission of the author.
 *     This copyrightextends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 */

#include <gtest/gtest.h>
#include <cpprest/json.h>
#include "Json.h"


// test of deserialization of premitive types
namespace JsonTest
{
namespace TestDeserializer
{
using namespace web;

TEST( DeSerilizaPirmitiveTest, SerializeInt )
{
    int i = 0;
    json::value jvalue = json::value( 10 );

    Json::FromJson( i, jvalue );
    ASSERT_EQ( 10, i );

    jvalue = json::value( 20 );
    Json::FromJson( &i, jvalue );
    ASSERT_EQ( 20, i );
}

TEST( DeSerilizaPirmitiveTest, SerializeVectInt )
{
    int i = 0;
    json::value jvalue = json::value::array( 3 );
    json::array &arr = jvalue.as_array();
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    std::vector<int> vec;

    Json::FromJson( vec, jvalue );

    ASSERT_EQ( vec.size(), jvalue.as_array().size() );
    auto itr = vec.begin();
    for ( auto &arrVal : jvalue.as_array() )
    {
        ASSERT_EQ( arrVal, *itr );
        ++itr;
    }

    vec.clear();

    Json::FromJson( &vec, jvalue );

    ASSERT_EQ( vec.size(), jvalue.as_array().size() );
    auto itr2 = vec.begin();
    for ( auto &arrVal : jvalue.as_array() )
    {
        ASSERT_EQ( arrVal, *itr2 );
        ++itr2;
    }
}

TEST( DeSerilizaPirmitiveTest, BoolTest )
{
    json::value jval = json::value( true );
    bool bval;
    bool *pbool = new bool( false );
    bool *pbool2 = nullptr;
    bool **pbool3 = nullptr;

    Json::FromJson( bval, jval );
    ASSERT_EQ( bval, true );


    bval = false;
    // bval is allocated
    Json::FromJson( &bval, jval );
    ASSERT_EQ( bval, true );

    Json::FromJson( pbool, jval );
    // pbool is allocated
    ASSERT_EQ( *pbool, true );
    delete pbool;

    //pbool2 is NOT allocated
    Json::FromJson( &pbool2, jval );
    ASSERT_EQ( *pbool2, true );
    delete pbool2;

    //pbool3 is allocated, but *pbbol3 is NOT
    pbool3 = new bool*();
    Json::FromJson( pbool3, jval );
    ASSERT_EQ( **pbool3, true );
    delete *pbool3;
    delete pbool3;
}

TEST( DeSerilizaPirmitiveTest, CharTest )
{
    json::value jval;

    char charVal = 'A';
    jval = json::value( charVal );
    charVal = 0;
    Json::FromJson( charVal, jval );
    ASSERT_EQ( 'A', charVal );

    const char *p = "Hello World!!";
    jval = json::value( U( p ) );

    char *p2 = nullptr;
    Json::FromJson( &p2, jval );
    ASSERT_TRUE( strcmp( p, p2 ) == 0 );
    delete p2;

    char *p3 = new char[strlen( p ) + 1];
    Json::FromJson( p3, jval );
    ASSERT_TRUE( strcmp( p, p3 ) == 0 );
    delete p3;

    char **p4 = new char*[strlen( p ) + 1];
    Json::FromJson( p4, jval );
    ASSERT_TRUE( strcmp( p, *p4 ) == 0 );
    delete *p4;
    delete p4;
}

TEST( DeSerilizaPirmitiveTest, StringTest )
{
    utility::string_t strT = utility::string_t( U( "Hello world..." ) );
    json::value jval = json::value( strT );

    std::string str;
    Json::FromJson( str, jval );
    ASSERT_TRUE( strT.compare( str ) == 0 );

    str = "";
    Json::FromJson( &str, jval );
    ASSERT_TRUE( strT.compare( str ) == 0 );

    std::string *strp = new std::string();
    Json::FromJson( strp, jval );
    ASSERT_TRUE( strT.compare( *strp ) == 0 );
    delete strp;

    std::string *strp2 = nullptr;
    Json::FromJson( &strp2, jval );
    ASSERT_TRUE( strT.compare( *strp2 ) == 0 );
    delete strp2;

    std::string **strp3 = new std::string*();
    Json::FromJson( strp3, jval );
    ASSERT_TRUE( strT.compare( **strp3 ) == 0 );
    delete *strp3;
    delete strp3;
}


TEST( DeSerilizaPirmitiveTest, Int8Test )
{
    json::value jval;

    //test int8_t
    int8_t byte = INT8_MIN;
    jval = json::value( byte );
    byte = 0;
    Json::FromJson( byte, jval );
    ASSERT_EQ( INT8_MIN, byte );
    byte = 0;
    Json::FromJson( &byte, jval );
    ASSERT_EQ( INT8_MIN, byte );

    byte = INT8_MAX;
    jval = json::value( byte );
    byte = 0;
    Json::FromJson( byte, jval );
    ASSERT_EQ( INT8_MAX, byte );
    byte = 0;
    Json::FromJson( &byte, jval );
    ASSERT_EQ( INT8_MAX, byte );

    // a value: min > value > max
    jval = json::value( 100 );
    int8_t *int8Ptr = nullptr;
    Json::FromJson( &int8Ptr, jval );
    ASSERT_EQ( 100, *int8Ptr );
    delete int8Ptr;

    int8_t **int8Ptr2 = new int8_t*();
    Json::FromJson( int8Ptr2, jval );
    ASSERT_EQ( 100, **int8Ptr2 );
    delete *int8Ptr2;
    delete int8Ptr2;

    //test uint8_t
    uint8_t ubyte = 0;
    jval = json::value( ubyte );
    ubyte = 1;
    Json::FromJson( ubyte, jval );
    ASSERT_EQ( 0, ubyte );
    ubyte = 1;
    Json::FromJson( &ubyte, jval );
    ASSERT_EQ( 0, ubyte );

    ubyte = UINT8_MAX;
    jval = json::value( ubyte );
    ubyte = 0;
    Json::FromJson( ubyte, jval );
    ASSERT_EQ( UINT8_MAX, ubyte );
    ubyte = 0;
    Json::FromJson( &ubyte, jval );
    ASSERT_EQ( UINT8_MAX, ubyte );

    // a value: min > value > max
    jval = json::value( 200 );
    uint8_t *uint8Ptr = nullptr;
    Json::FromJson( &uint8Ptr, jval );
    ASSERT_EQ( 200, *uint8Ptr );
    delete uint8Ptr;

    uint8_t **uint8Ptr2 = new uint8_t*();
    Json::FromJson( uint8Ptr2, jval );
    ASSERT_EQ( 200, **uint8Ptr2 );
    delete *uint8Ptr2;
    delete uint8Ptr2;
}

TEST( DeSerilizaPirmitiveTest, Int16Test )
{
    json::value jval;

    //test int16_t
    int16_t int16 = INT16_MIN;
    jval = json::value( int16 );
    int16 = 0;
    Json::FromJson( int16, jval );
    ASSERT_EQ( INT16_MIN, int16 );
    int16 = 0;
    Json::FromJson( &int16, jval );
    ASSERT_EQ( INT16_MIN, int16 );

    int16 = INT16_MAX;
    jval = json::value( int16 );
    int16 = 0;
    Json::FromJson( int16, jval );
    ASSERT_EQ( INT16_MAX, int16 );
    int16 = 0;
    Json::FromJson( &int16, jval );
    ASSERT_EQ( INT16_MAX, int16 );

    // a value: min > value > max
    jval = json::value( 30000 );
    int16_t *int16Ptr = nullptr;
    Json::FromJson( &int16Ptr, jval );
    ASSERT_EQ( 30000, *int16Ptr );
    delete int16Ptr;

    int16_t **int16Ptr2 = new int16_t*();
    Json::FromJson( int16Ptr2, jval );
    ASSERT_EQ( 30000, **int16Ptr2 );
    delete *int16Ptr2;
    delete int16Ptr2;


    //test uint16_t
    uint16_t uini16 = 0;
    jval = json::value( uini16 );
    uini16 = 1;
    Json::FromJson( uini16, jval );
    ASSERT_EQ( 0, uini16 );
    uini16 = 1;
    Json::FromJson( &uini16, jval );
    ASSERT_EQ( 0, uini16 );

    uini16 = UINT16_MAX;
    jval = json::value( uini16 );
    uini16 = 0;
    Json::FromJson( uini16, jval );
    ASSERT_EQ( UINT16_MAX, uini16 );
    uini16 = 0;
    Json::FromJson( &uini16, jval );
    ASSERT_EQ( UINT16_MAX, uini16 );

    // a value: min > value > max
    jval = json::value( 40000 );
    uint16_t *uint16Ptr = nullptr;
    Json::FromJson( &uint16Ptr, jval );
    ASSERT_EQ( 40000, *uint16Ptr );
    delete uint16Ptr;

    uint16_t **uint16Ptr2 = new uint16_t*();
    Json::FromJson( uint16Ptr2, jval );
    ASSERT_EQ( 40000, **uint16Ptr2 );
    delete *uint16Ptr2;
    delete uint16Ptr2;
}


TEST( DeSerilizaPirmitiveTest, Int32Test )
{
    json::value jval;

    //test int16_t
    int32_t int32 = INT32_MIN;
    jval = json::value( int32 );
    int32 = 0;
    Json::FromJson( int32, jval );
    ASSERT_EQ( INT32_MIN, int32 );
    int32 = 0;
    Json::FromJson( &int32, jval );
    ASSERT_EQ( INT32_MIN, int32 );

    int32 = INT32_MAX;
    jval = json::value( int32 );
    int32 = 0;
    Json::FromJson( int32, jval );
    ASSERT_EQ( INT32_MAX, int32 );
    int32 = 0;
    Json::FromJson( &int32, jval );
    ASSERT_EQ( INT32_MAX, int32 );

    // a value: min > value > max
    jval = json::value( 2147483640 );
    int32_t *int32Ptr = nullptr;
    Json::FromJson( &int32Ptr, jval );
    ASSERT_EQ( 2147483640, *int32Ptr );
    delete int32Ptr;

    int32_t **int32Ptr2 = new int32_t*();
    Json::FromJson( int32Ptr2, jval );
    ASSERT_EQ( 2147483640, **int32Ptr2 );
    delete *int32Ptr2;
    delete int32Ptr2;


    //test uint16_t
    uint32_t uini32 = 0;
    jval = json::value( uini32 );
    uini32 = 1;
    Json::FromJson( uini32, jval );
    ASSERT_EQ( 0, uini32 );
    uini32 = 1;
    Json::FromJson( &uini32, jval );
    ASSERT_EQ( 0, uini32 );

    uini32 = UINT32_MAX;
    jval = json::value( uini32 );
    uini32 = 0;
    Json::FromJson( uini32, jval );
    ASSERT_EQ( UINT32_MAX, uini32 );
    uini32 = 0;
    Json::FromJson( &uini32, jval );
    ASSERT_EQ( UINT32_MAX, uini32 );

    // a value: min > value > max
    jval = json::value( 4294967290 );
    uint32_t *uint32Ptr = nullptr;
    Json::FromJson( &uint32Ptr, jval );
    ASSERT_EQ( 4294967290, *uint32Ptr );
    delete uint32Ptr;

    uint32_t **uint32Ptr2 = new uint32_t*();
    Json::FromJson( uint32Ptr2, jval );
    ASSERT_EQ( 4294967290, **uint32Ptr2 );
    delete *uint32Ptr2;
    delete uint32Ptr2;
}


TEST( DeSerilizaPirmitiveTest, Int64Test )
{
    json::value jval;

    //test int16_t
    int64_t int64 = INT64_MIN;
    jval = json::value( int64 );
    int64 = 0;
    Json::FromJson( int64, jval );
    ASSERT_EQ( INT64_MIN, int64 );
    int64 = 0;
    Json::FromJson( &int64, jval );
    ASSERT_EQ( INT64_MIN, int64 );

    int64 = INT64_MAX;
    jval = json::value( int64 );
    int64 = 0;
    Json::FromJson( int64, jval );
    ASSERT_EQ( INT64_MAX, int64 );
    int64 = 0;
    Json::FromJson( &int64, jval );
    ASSERT_EQ( INT64_MAX, int64 );

    // a value: min > value > max
    jval = json::value( 9223372036854775800 );
    int64_t *int64Ptr = nullptr;
    Json::FromJson( &int64Ptr, jval );
    ASSERT_EQ( 9223372036854775800, *int64Ptr );
    delete int64Ptr;

    int64_t **int64Ptr2 = new int64_t*();
    Json::FromJson( int64Ptr2, jval );
    ASSERT_EQ( 9223372036854775800, **int64Ptr2 );
    delete *int64Ptr2;
    delete int64Ptr2;


    //test uint16_t
    uint64_t uini64 = 0;
    jval = json::value( uini64 );
    uini64 = 1;
    Json::FromJson( uini64, jval );
    ASSERT_EQ( 0, uini64 );
    uini64 = 1;
    Json::FromJson( &uini64, jval );
    ASSERT_EQ( 0, uini64 );

    uini64 = UINT64_MAX;
    jval = json::value( uini64 );
    uini64 = 0;
    Json::FromJson( uini64, jval );
    ASSERT_EQ( UINT64_MAX, uini64 );
    uini64 = 0;
    Json::FromJson( &uini64, jval );
    ASSERT_EQ( UINT64_MAX, uini64 );

    // a value: min > value > max
    jval = json::value( 18446744073709551610UL );
    uint64_t *uint64Ptr = nullptr;
    Json::FromJson( &uint64Ptr, jval );
    ASSERT_EQ( 18446744073709551610UL, *uint64Ptr );
    delete uint64Ptr;

    uint64_t **uint64Ptr2 = new uint64_t*();
    Json::FromJson( uint64Ptr2, jval );
    ASSERT_EQ( 18446744073709551610UL, **uint64Ptr2 );
    delete *uint64Ptr2;
    delete uint64Ptr2;
}


TEST( DeSerilizaPirmitiveTest, FloatTest )
{
    json::value jval;

    float fval = 15.05;
    jval = json::value( fval );
    fval = 0;
    Json::FromJson( fval, jval );
    ASSERT_FLOAT_EQ( 15.05, fval );
    fval = 0;
    Json::FromJson( &fval, jval );
    ASSERT_FLOAT_EQ( 15.05, fval );

    float *fptr = nullptr;
    Json::FromJson( &fptr, jval );
    ASSERT_FLOAT_EQ( 15.05, *fptr );
    delete fptr;

    float **fptr2 = new float*();
    Json::FromJson( fptr2, jval );
    ASSERT_FLOAT_EQ( 15.05, **fptr2 );
    delete *fptr2;
    delete fptr2;
}

TEST( DeSerilizaPirmitiveTest, DoubleTest )
{
    json::value jval;

    double fval = 15.05;
    jval = json::value( fval );
    fval = 0;
    Json::FromJson( fval, jval );
    ASSERT_DOUBLE_EQ( 15.05, fval );
    fval = 0;
    Json::FromJson( &fval, jval );
    ASSERT_DOUBLE_EQ( 15.05, fval );

    double *fptr = nullptr;
    Json::FromJson( &fptr, jval );
    ASSERT_DOUBLE_EQ( 15.05, *fptr );
    delete fptr;

    double **fptr2 = new double*();
    Json::FromJson( fptr2, jval );
    ASSERT_DOUBLE_EQ( 15.05, **fptr2 );
    delete *fptr2;
    delete fptr2;
}

} //namespace TestDeserializer
} // namespace JsonTest
