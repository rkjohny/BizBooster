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
#include "Json.h"

using namespace web;
using namespace std;
using namespace Json;

namespace JsonTest
{
namespace TestSerializer
{


class SerializePremitiveTest : public ::testing::Test
{
public:
    char *strPtr;

    SerializePremitiveTest() = default;
    virtual ~SerializePremitiveTest() = default;

    void SetUp() override
    {
        strPtr = new char[100];
        strcpy( strPtr, "Hello World!" );
    }

    void TearDown() override
    {
        delete strPtr;
    }

}; // class SerializePremitiveTest

TEST_F( SerializePremitiveTest, PremitiveInt )
{
    json::value jval;
    int intVal = 10;

    //serialize for integer
    jval = Json::ToJson( 10 );
    ASSERT_EQ( 10, jval.as_integer() );
    jval = Json::ToJson( int( 10 ) );
    ASSERT_EQ( 10, jval.as_integer() );
    jval = Json::ToJson( std::move( intVal ) );
    ASSERT_EQ( intVal, jval.as_integer() );

    jval = Json::ToJson( intVal );
    ASSERT_TRUE( jval.is_number() );
    ASSERT_TRUE( jval.as_number().is_int32() );
    ASSERT_TRUE( jval.as_number().to_int32() == intVal );
    ASSERT_EQ( intVal, jval.as_integer() );

    unsigned int uintVal = 20;
    jval = Json::ToJson( uintVal );
    ASSERT_TRUE( jval.is_number() );
    ASSERT_TRUE( jval.as_number().is_uint32() );
    ASSERT_TRUE( jval.as_number().to_uint32() == uintVal );
    ASSERT_EQ( uintVal, jval.as_integer() );

    const int intVal2 = 10;
    jval = Json::ToJson( intVal2 );
    ASSERT_EQ( intVal2, jval.as_integer() );
    int &intVal3 = intVal;
    jval = Json::ToJson( intVal3 );
    ASSERT_EQ( intVal3, jval.as_integer() );
    const int &intVal4 = intVal2;
    jval = Json::ToJson( intVal4 );
    ASSERT_EQ( intVal4, jval.as_integer() );
    int const& intValue5 = intVal;
    jval = Json::ToJson( intValue5 );
    ASSERT_EQ( intValue5, jval.as_integer() );

    int *intPtr = &intVal;
    jval = Json::ToJson( intPtr );
    ASSERT_EQ( *intPtr, jval.as_integer() );
    const int *intPtr2 = &intVal;
    jval = Json::ToJson( intPtr2 );
    ASSERT_EQ( *intPtr2, jval.as_integer() );
    int * const intPtr3 = &intVal;
    jval = Json::ToJson( intPtr3 );
    ASSERT_EQ( *intPtr3, jval.as_integer() );
    const int * const intPtr4 = &intVal;
    jval = Json::ToJson( intPtr4 );
    ASSERT_EQ( *intPtr4, jval.as_integer() );
}

TEST_F( SerializePremitiveTest, PremitiveLong )
{
    json::value jval;
    long longVal = 10;

    jval = Json::ToJson( 10L );
    ASSERT_TRUE( jval.is_number() );
    ASSERT_TRUE( jval.as_number().is_int64() );
    ASSERT_TRUE( jval.as_number().to_int64() == 10L );

    ASSERT_EQ( 10L, jval.as_integer() );
    jval = Json::ToJson( long( 10 ) );
    ASSERT_EQ( 10L, jval.as_integer() );
    jval = Json::ToJson( std::move( longVal ) );
    ASSERT_EQ( longVal, jval.as_integer() );

    jval = Json::ToJson( longVal );
    ASSERT_TRUE( jval.is_number() );
    ASSERT_TRUE( jval.as_number().is_int64() );
    ASSERT_TRUE( jval.as_number().to_int64() == longVal );
    ASSERT_EQ( longVal, jval.as_integer() );


    unsigned long ulongVal = 20L;
    jval = Json::ToJson( ulongVal );
    ASSERT_TRUE( jval.is_number() );
    ASSERT_TRUE( jval.as_number().is_uint64() );
    ASSERT_TRUE( jval.as_number().to_uint64() == ulongVal );
    ASSERT_EQ( ulongVal, jval.as_integer() );


    const long longVal2 = 10L;
    jval = Json::ToJson( longVal2 );
    ASSERT_EQ( longVal2, jval.as_integer() );
    long &longVal3 = longVal;
    jval = Json::ToJson( longVal3 );
    ASSERT_EQ( longVal3, jval.as_integer() );
    const long &longVal4 = longVal2;
    jval = Json::ToJson( longVal4 );
    ASSERT_EQ( longVal4, jval.as_integer() );
    long const& longValue5 = longVal;
    jval = Json::ToJson( longValue5 );
    ASSERT_EQ( longValue5, jval.as_integer() );

    long *longPtr = &longVal;
    jval = Json::ToJson( longPtr );
    ASSERT_EQ( *longPtr, jval.as_integer() );
    const long *longPtr2 = &longVal;
    jval = Json::ToJson( longPtr2 );
    ASSERT_EQ( *longPtr2, jval.as_integer() );
    long * const longPtr3 = &longVal;
    jval = Json::ToJson( longPtr3 );
    ASSERT_EQ( *longPtr3, jval.as_integer() );
    const long * const longPtr4 = &longVal;
    jval = Json::ToJson( longPtr4 );
    ASSERT_EQ( *longPtr4, jval.as_integer() );
}

TEST_F( SerializePremitiveTest, PremitiveBool )
{
    json::value jval;
    bool boolVal = true;

    jval = Json::ToJson( true );
    ASSERT_EQ( true, jval.as_bool() );
    jval = Json::ToJson( bool( true ) );
    ASSERT_EQ( true, jval.as_bool() );
    jval = Json::ToJson( std::move( boolVal ) );
    ASSERT_EQ( boolVal, jval.as_bool() );

    jval = Json::ToJson( boolVal );
    ASSERT_EQ( boolVal, jval.as_bool() );
    const bool boolVal2 = true;
    jval = Json::ToJson( boolVal2 );
    ASSERT_EQ( boolVal2, jval.as_bool() );
    bool &boolVal3 = boolVal;
    jval = Json::ToJson( boolVal3 );
    ASSERT_EQ( boolVal3, jval.as_bool() );
    const bool &boolVal4 = boolVal2;
    jval = Json::ToJson( boolVal4 );
    ASSERT_EQ( boolVal4, jval.as_bool() );
    bool const& boolValue5 = boolVal;
    jval = Json::ToJson( boolValue5 );
    ASSERT_EQ( boolValue5, jval.as_bool() );

    bool *boolPtr = &boolVal;
    jval = Json::ToJson( boolPtr );
    ASSERT_EQ( *boolPtr, jval.as_bool() );
    const bool *boolPtr2 = &boolVal;
    jval = Json::ToJson( boolPtr2 );
    ASSERT_EQ( *boolPtr2, jval.as_bool() );
    bool * const boolPtr3 = &boolVal;
    jval = Json::ToJson( boolPtr3 );
    ASSERT_EQ( *boolPtr3, jval.as_bool() );
    const bool * const boolPtr4 = &boolVal;
    jval = Json::ToJson( boolPtr4 );
    ASSERT_EQ( *boolPtr4, jval.as_bool() );
}

TEST_F( SerializePremitiveTest, PremitiveFloat )
{
    json::value jval;
    float decimalVal = 10.51;

    jval = Json::ToJson( 10.51 );
    ASSERT_FLOAT_EQ( 10.51, jval.as_double() );
    jval = Json::ToJson( float( 10.51 ) );
    ASSERT_FLOAT_EQ( 10.51, jval.as_double() );
    jval = Json::ToJson( std::move( decimalVal ) );
    ASSERT_FLOAT_EQ( decimalVal, jval.as_double() );

    jval = Json::ToJson( decimalVal );
    ASSERT_FLOAT_EQ( decimalVal, jval.as_double() );
    const float decimalVal2 = 10.51;
    jval = Json::ToJson( decimalVal2 );
    ASSERT_FLOAT_EQ( decimalVal2, jval.as_double() );
    float &decimalVal3 = decimalVal;
    jval = Json::ToJson( decimalVal3 );
    ASSERT_FLOAT_EQ( decimalVal3, jval.as_double() );
    const float &decimalVal4 = decimalVal2;
    jval = Json::ToJson( decimalVal4 );
    ASSERT_FLOAT_EQ( decimalVal4, jval.as_double() );
    float const& decimalValue5 = decimalVal;
    jval = Json::ToJson( decimalValue5 );
    ASSERT_FLOAT_EQ( decimalValue5, jval.as_double() );

    float *decimalPtr = &decimalVal;
    jval = Json::ToJson( decimalPtr );
    ASSERT_FLOAT_EQ( *decimalPtr, jval.as_double() );
    const float *decialPtr2 = &decimalVal;
    jval = Json::ToJson( decialPtr2 );
    ASSERT_FLOAT_EQ( *decialPtr2, jval.as_double() );
    float * const decimalPtr3 = &decimalVal;
    jval = Json::ToJson( decimalPtr3 );
    ASSERT_FLOAT_EQ( *decimalPtr3, jval.as_double() );
    const float * const decimalPtr4 = &decimalVal;
    jval = Json::ToJson( decimalPtr4 );
    ASSERT_FLOAT_EQ( *decimalPtr4, jval.as_double() );
}

TEST_F( SerializePremitiveTest, PremitiveDouble )
{
    json::value jval;
    double decimalVal = 10.51;

    jval = Json::ToJson( 10.51 );
    ASSERT_DOUBLE_EQ( 10.51, jval.as_double() );
    jval = Json::ToJson( double( 10.51 ) );
    ASSERT_DOUBLE_EQ( 10.51, jval.as_double() );
    jval = Json::ToJson( std::move( decimalVal ) );
    ASSERT_DOUBLE_EQ( decimalVal, jval.as_double() );

    jval = Json::ToJson( decimalVal );
    ASSERT_DOUBLE_EQ( decimalVal, jval.as_double() );
    const double decimalVal2 = 10.51;
    jval = Json::ToJson( decimalVal2 );
    ASSERT_DOUBLE_EQ( decimalVal2, jval.as_double() );
    double &decimalVal3 = decimalVal;
    jval = Json::ToJson( decimalVal3 );
    ASSERT_DOUBLE_EQ( decimalVal3, jval.as_double() );
    const double &decimalVal4 = decimalVal2;
    jval = Json::ToJson( decimalVal4 );
    ASSERT_DOUBLE_EQ( decimalVal4, jval.as_double() );
    double const& decimalValue5 = decimalVal;
    jval = Json::ToJson( decimalValue5 );
    ASSERT_DOUBLE_EQ( decimalValue5, jval.as_double() );

    double *decimalPtr = &decimalVal;
    jval = Json::ToJson( decimalPtr );
    ASSERT_DOUBLE_EQ( *decimalPtr, jval.as_double() );
    const double *decialPtr2 = &decimalVal;
    jval = Json::ToJson( decialPtr2 );
    ASSERT_DOUBLE_EQ( *decialPtr2, jval.as_double() );
    double * const decimalPtr3 = &decimalVal;
    jval = Json::ToJson( decimalPtr3 );
    ASSERT_DOUBLE_EQ( *decimalPtr3, jval.as_double() );
    const double * const decimalPtr4 = &decimalVal;
    jval = Json::ToJson( decimalPtr4 );
    ASSERT_DOUBLE_EQ( *decimalPtr4, jval.as_double() );
}

TEST_F( SerializePremitiveTest, PremitiveChar )
{
    json::value jval;
    int intVal = 'A';
    char charValue = 'A';

    jval = Json::ToJson( 'A' );
    ASSERT_EQ( 65, jval.as_integer() );
    jval = Json::ToJson( char( 'A' ) );
    ASSERT_EQ( 65, jval.as_integer() );
    jval = Json::ToJson( std::move( charValue ) );
    ASSERT_EQ( intVal, jval.as_integer() );

    jval = Json::ToJson( charValue );
    ASSERT_TRUE( jval.is_number() );
    ASSERT_TRUE( jval.as_number().is_int32() );
    ASSERT_TRUE( jval.as_number().to_int32() == intVal );
    ASSERT_EQ( intVal, jval.as_integer() );

    unsigned char ucharVal = 'A';
    jval = Json::ToJson( ucharVal );
    ASSERT_TRUE( jval.is_number() );
    ASSERT_TRUE( jval.as_number().is_int32() );
    ASSERT_TRUE( jval.as_number().to_int32() == intVal );
    ASSERT_EQ( intVal, jval.as_integer() );

    const char charVal2 = 'A';
    jval = Json::ToJson( charVal2 );
    ASSERT_EQ( intVal, jval.as_integer() );
    char &charVal3 = charValue;
    jval = Json::ToJson( charVal3 );
    ASSERT_EQ( intVal, jval.as_integer() );
    const char &charVal4 = charVal2;
    jval = Json::ToJson( charVal4 );
    ASSERT_EQ( intVal, jval.as_integer() );
    char const& charValue5 = intVal;
    jval = Json::ToJson( charValue5 );
    ASSERT_EQ( intVal, jval.as_integer() );
}

TEST_F( SerializePremitiveTest, PremitiveCharPtr )
{
    json::value jval;
    std::string strVal;
    char *charPtr = strPtr;

    jval = Json::ToJson( "Hello World!" );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( "Hello World!" ).compare( strVal ) );

    jval = Json::ToJson( std::move( charPtr ) );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr ).compare( strVal ) );

    jval = Json::ToJson( charPtr );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr ).compare( strVal ) );

    const char *charPtr2 = strPtr;
    jval = Json::ToJson( std::move( charPtr2 ) );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr2 ).compare( strVal ) );

    jval = Json::ToJson( charPtr2 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr2 ).compare( strVal ) );

    char * const charPtr3 = strPtr;
    jval = Json::ToJson( std::move( charPtr3 ) );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr3 ).compare( strVal ) );

    jval = Json::ToJson( charPtr3 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr3 ).compare( strVal ) );

    const char* const charPtr4 = strPtr;
    jval = Json::ToJson( std::move( charPtr4 ) );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr4 ).compare( strVal ) );

    jval = Json::ToJson( charPtr4 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, std::string( charPtr4 ).compare( strVal ) );

    jval = Json::ToJson( *charPtr4 );
    ASSERT_TRUE( ( int )*charPtr4 == jval.as_integer() );

    jval = Json::ToJson( std::move( *charPtr4 ) );
    ASSERT_TRUE( ( int )*charPtr4 == jval.as_integer() );
}


TEST_F( SerializePremitiveTest, STLString )
{
    json::value jval;
    std::string strVal;

    std::string str = "hello world";
    jval = Json::ToJson( std::move( str ) );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str.compare( strVal ) );

    jval = Json::ToJson( str );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str.compare( strVal ) );

    const std::string str2 = "hello world";
    jval = Json::ToJson( std::move( str2 ) );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str2.compare( strVal ) );

    jval = Json::ToJson( str2 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str2.compare( strVal ) );

    std::string *str3 = &str;
    jval = Json::ToJson( str3 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str3->compare( strVal ) );

    const std::string *str4 = &str;
    jval = Json::ToJson( str4 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str4->compare( strVal ) );

    std::string * const str5 = &str;
    jval = Json::ToJson( str5 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str5->compare( strVal ) );

    const std::string * const str6 = &str;
    jval = Json::ToJson( str6 );
    strVal = utility::conversions::to_utf8string( jval.as_string() );
    ASSERT_EQ( 0, str6->compare( strVal ) );
}

} // namespace SerializingTest
} //namespave JsonTest

