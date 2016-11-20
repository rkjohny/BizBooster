/*
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com)
 *     The information contained here-in is the property of Rezaul Karim and
 *     is not to be disclosed or used without prior written permission of Rezaul Karim.
 *     This copyright extends to all media in which this information may be preserved
 *     including magnetic storage, computer print-out or visual display.
 *     Please refer to License.txt file for more details.
 */

#include <gtest/gtest.h>
#include "TypeTratits.h"
#include <string>

using namespace Json;
using namespace std;

namespace JsonTest
{

#define ATRUE(TYPE, OPERAND) \
    ASSERT_TRUE(OPERAND<TYPE&&>::Value); \
    ASSERT_TRUE(OPERAND<TYPE&>::Value); \
    ASSERT_TRUE(OPERAND<TYPE>::Value); \
    ASSERT_TRUE(OPERAND<const TYPE&&>::Value); \
    ASSERT_TRUE(OPERAND<const TYPE&>::Value); \
    ASSERT_TRUE(OPERAND<const TYPE>::Value);

#define AFALSE(TYPE, OPERAND) \
    ASSERT_FALSE(OPERAND<TYPE&&>::Value); \
    ASSERT_FALSE(OPERAND<TYPE&>::Value); \
    ASSERT_FALSE(OPERAND<TYPE>::Value); \
    ASSERT_FALSE(OPERAND<const TYPE&&>::Value); \
    ASSERT_FALSE(OPERAND<const TYPE&>::Value); \
    ASSERT_FALSE(OPERAND<const TYPE>::Value);

TEST( TepeTraitsTest, BoolTest )
{
    //type: bool
    AFALSE( bool, Is_Char );
    ATRUE( bool, Is_Bool ); //true
    AFALSE( bool, Is_Int8 );
    AFALSE( bool, Is_UInt8 );
    AFALSE( bool, Is_Int16 );
    AFALSE( bool, Is_UInt16 );
    AFALSE( bool, Is_Int32 );
    AFALSE( bool, Is_UInt32 );
    AFALSE( bool, Is_Int64 );
    AFALSE( bool, Is_UInt64 );
    AFALSE( bool, Is_Integer );
    AFALSE( bool, Is_Float );
    AFALSE( bool, Is_Double );
    AFALSE( bool, Is_LongDouble );
    AFALSE( bool, Is_Decimal );
    ATRUE( bool, Is_Premitive ); //true
    AFALSE( bool, Is_String );
    AFALSE( bool, Is_Vector );
    AFALSE( bool, Is_Object );
}

TEST( TepeTraitsTest, CharTest )
{
    //type: char
    ATRUE( char, Is_Char ); //true
    AFALSE( char, Is_Bool );
    AFALSE( char, Is_Int8 );
    AFALSE( char, Is_UInt8 );
    AFALSE( char, Is_Int16 );
    AFALSE( char, Is_UInt16 );
    AFALSE( char, Is_Int32 );
    AFALSE( char, Is_UInt32 );
    AFALSE( char, Is_Int64 );
    AFALSE( char, Is_UInt64 );
    AFALSE( char, Is_Integer );
    AFALSE( char, Is_Float );
    AFALSE( char, Is_Double );
    AFALSE( char, Is_LongDouble );
    AFALSE( char, Is_Decimal );
    ATRUE( char, Is_Premitive ); //true
    AFALSE( char, Is_String );
    AFALSE( char, Is_Vector );
    AFALSE( char, Is_Object );
}

TEST( TepeTraitsTest, Int8Test )
{
    //type: signed char = uint8_t
    AFALSE( int8_t, Is_Char );
    AFALSE( int8_t, Is_Bool );
    ATRUE( int8_t, Is_Int8 ); //true
    AFALSE( int8_t, Is_UInt8 );
    AFALSE( int8_t, Is_Int16 );
    AFALSE( int8_t, Is_UInt16 );
    AFALSE( int8_t, Is_Int32 );
    AFALSE( int8_t, Is_UInt32 );
    AFALSE( int8_t, Is_Int64 );
    AFALSE( int8_t, Is_UInt64 );
    ATRUE( int8_t, Is_Integer ); //true
    AFALSE( int8_t, Is_Float );
    AFALSE( int8_t, Is_Double );
    AFALSE( int8_t, Is_LongDouble );
    AFALSE( int8_t, Is_Decimal );
    ATRUE( int8_t, Is_Premitive ); //true
    AFALSE( int8_t, Is_String );
    AFALSE( int8_t, Is_Vector );
    AFALSE( int8_t, Is_Object );

    //type: unsigned char = uint8_t
    AFALSE( uint8_t, Is_Char );
    AFALSE( uint8_t, Is_Bool );
    AFALSE( uint8_t, Is_Int8 );
    ATRUE( uint8_t, Is_UInt8 ); //true
    AFALSE( uint8_t, Is_Int16 );
    AFALSE( uint8_t, Is_UInt16 );
    AFALSE( uint8_t, Is_Int32 );
    AFALSE( uint8_t, Is_UInt32 );
    AFALSE( uint8_t, Is_Int64 );
    AFALSE( uint8_t, Is_UInt64 );
    ATRUE( uint8_t, Is_Integer ); //true
    AFALSE( uint8_t, Is_Float );
    AFALSE( uint8_t, Is_Double );
    AFALSE( uint8_t, Is_LongDouble );
    AFALSE( uint8_t, Is_Decimal );
    ATRUE( uint8_t, Is_Premitive ); //true
    AFALSE( uint8_t, Is_String );
    AFALSE( uint8_t, Is_Vector );
    AFALSE( uint8_t, Is_Object );
}

TEST( TepeTraitsTest, Int16Test )
{
    //type: signed short int = int16_t
    AFALSE( int16_t, Is_Char );
    AFALSE( int16_t, Is_Bool );
    AFALSE( int16_t, Is_Int8 );
    AFALSE( int16_t, Is_UInt8 );
    ATRUE( int16_t, Is_Int16 ); //true
    AFALSE( int16_t, Is_UInt16 );
    AFALSE( int16_t, Is_Int32 );
    AFALSE( int16_t, Is_UInt32 );
    AFALSE( int16_t, Is_Int64 );
    AFALSE( int16_t, Is_UInt64 );
    ATRUE( int16_t, Is_Integer ); //true
    AFALSE( int16_t, Is_Float );
    AFALSE( int16_t, Is_Double );
    AFALSE( int16_t, Is_LongDouble );
    AFALSE( int16_t, Is_Decimal );
    ATRUE( int16_t, Is_Premitive ); //true
    AFALSE( int16_t, Is_String );
    AFALSE( int16_t, Is_Vector );
    AFALSE( int16_t, Is_Object );

    //type: unsigned short int = uint16_t
    AFALSE( uint16_t, Is_Char );
    AFALSE( uint16_t, Is_Bool );
    AFALSE( uint16_t, Is_Int8 );
    AFALSE( uint16_t, Is_UInt8 );
    AFALSE( uint16_t, Is_Int16 );
    ATRUE( uint16_t, Is_UInt16 ); //true
    AFALSE( uint16_t, Is_Int32 );
    AFALSE( uint16_t, Is_UInt32 );
    AFALSE( uint16_t, Is_Int64 );
    AFALSE( uint16_t, Is_UInt64 );
    ATRUE( uint16_t, Is_Integer ); //true
    AFALSE( uint16_t, Is_Float );
    AFALSE( uint16_t, Is_Double );
    AFALSE( uint16_t, Is_LongDouble );
    AFALSE( uint16_t, Is_Decimal );
    ATRUE( uint16_t, Is_Premitive ); //true
    AFALSE( uint16_t, Is_String );
    AFALSE( uint16_t, Is_Vector );
    AFALSE( uint16_t, Is_Object );
}

TEST( TepeTraitsTest, Int32Test )
{
    //type: signed int = int32_t
    AFALSE( int32_t, Is_Char );
    AFALSE( int32_t, Is_Bool );
    AFALSE( int32_t, Is_Int8 );
    AFALSE( int32_t, Is_UInt8 );
    AFALSE( int32_t, Is_Int16 );
    AFALSE( int32_t, Is_UInt16 );
    ATRUE( int32_t, Is_Int32 ); //true
    AFALSE( int32_t, Is_UInt32 );
    AFALSE( int32_t, Is_Int64 );
    AFALSE( int32_t, Is_UInt64 );
    ATRUE( int32_t, Is_Integer ); //true
    AFALSE( int32_t, Is_Float );
    AFALSE( int32_t, Is_Double );
    AFALSE( int32_t, Is_LongDouble );
    AFALSE( int32_t, Is_Decimal );
    ATRUE( int32_t, Is_Premitive ); //true
    AFALSE( int32_t, Is_String );
    AFALSE( int32_t, Is_Vector );
    AFALSE( int32_t, Is_Object );

    //type: unsigned int = uint32_t
    AFALSE( uint32_t, Is_Char );
    AFALSE( uint32_t, Is_Bool );
    AFALSE( uint32_t, Is_Int8 );
    AFALSE( uint32_t, Is_UInt8 );
    AFALSE( uint32_t, Is_Int16 );
    AFALSE( uint32_t, Is_UInt16 );
    AFALSE( uint32_t, Is_Int32 );
    ATRUE( uint32_t, Is_UInt32 ); // true
    AFALSE( uint32_t, Is_Int64 );
    AFALSE( uint32_t, Is_UInt64 );
    ATRUE( uint32_t, Is_Integer ); //true
    AFALSE( uint32_t, Is_Float );
    AFALSE( uint32_t, Is_Double );
    AFALSE( uint32_t, Is_LongDouble );
    AFALSE( uint32_t, Is_Decimal );
    ATRUE( uint32_t, Is_Premitive ); //true
    AFALSE( uint32_t, Is_String );
    AFALSE( uint32_t, Is_Vector );
    AFALSE( uint32_t, Is_Object );
}

TEST( TepeTraitsTest, Int64Test )
{
    /**
     * type: in 64 bit WORD SIZE signed long int = int64_t
     * in 32 bit WORD SIZE signed long long int = int64_t
     */
    AFALSE( int64_t, Is_Char );
    AFALSE( int64_t, Is_Bool );
    AFALSE( int64_t, Is_Int8 );
    AFALSE( int64_t, Is_UInt8 );
    AFALSE( int64_t, Is_Int16 );
    AFALSE( int64_t, Is_UInt16 );
    AFALSE( int64_t, Is_Int32 );
    AFALSE( int64_t, Is_UInt32 );
    ATRUE( int64_t, Is_Int64 ); //true
    AFALSE( int64_t, Is_UInt64 );
    ATRUE( int64_t, Is_Integer ); //true
    AFALSE( int64_t, Is_Float );
    AFALSE( int64_t, Is_Double );
    AFALSE( int64_t, Is_LongDouble );
    AFALSE( int64_t, Is_Decimal );
    ATRUE( int64_t, Is_Premitive ); //true
    AFALSE( int64_t, Is_String );
    AFALSE( int64_t, Is_Vector );
    AFALSE( int64_t, Is_Object );

    /**
     * type: in 64 bit WORD SIZE unsigned long int = uint64_t
     * in 32 bit WORD SIZE unsigned long long int = uint64_t
     */
    AFALSE( uint64_t, Is_Char );
    AFALSE( uint64_t, Is_Bool );
    AFALSE( uint64_t, Is_Int8 );
    AFALSE( uint64_t, Is_UInt8 );
    AFALSE( uint64_t, Is_Int16 );
    AFALSE( uint64_t, Is_UInt16 );
    AFALSE( uint64_t, Is_Int32 );
    AFALSE( uint64_t, Is_UInt32 );
    AFALSE( uint64_t, Is_Int64 );
    ATRUE( uint64_t, Is_UInt64 ); //true
    ATRUE( uint64_t, Is_Integer ); //true
    AFALSE( uint64_t, Is_Float );
    AFALSE( uint64_t, Is_Double );
    AFALSE( uint64_t, Is_LongDouble );
    AFALSE( uint64_t, Is_Decimal );
    ATRUE( uint64_t, Is_Premitive ); //true
    AFALSE( uint64_t, Is_String );
    AFALSE( uint64_t, Is_Vector );
    AFALSE( uint64_t, Is_Object );
}

TEST( TypeTraitsTest, LongTest )
{
    /**
     * type: in 64 bit WORD SIZE signed long int = int64_t
     * in 32 bit WORD SIZE signed long long int = int64_t and long int = int32_t
     */
#if __WORDSIZE == 64

    AFALSE( long long, Is_Char );
    AFALSE( long long, Is_Bool );
    AFALSE( long long, Is_Int8 );
    AFALSE( long long, Is_UInt8 );
    AFALSE( long long, Is_Int16 );
    AFALSE( long long, Is_UInt16 );
    AFALSE( long long, Is_Int32 );
    AFALSE( long long, Is_UInt32 );
    ATRUE( long long, Is_Int64 ); // true
    AFALSE( long long, Is_UInt64 );
    ATRUE( long long, Is_Integer ); //true
    AFALSE( long long, Is_Float );
    AFALSE( long long, Is_Double );
    AFALSE( long long, Is_LongDouble );
    AFALSE( long long, Is_Decimal );
    ATRUE( long long, Is_Premitive ); //true
    AFALSE( long long, Is_String );
    AFALSE( long long, Is_Vector );
    AFALSE( long long, Is_Object );


    AFALSE( unsigned long long, Is_Char );
    AFALSE( unsigned long long, Is_Bool );
    AFALSE( unsigned long long, Is_Int8 );
    AFALSE( unsigned long long, Is_UInt8 );
    AFALSE( unsigned long long, Is_Int16 );
    AFALSE( unsigned long long, Is_UInt16 );
    AFALSE( unsigned long long, Is_Int32 );
    AFALSE( unsigned long long, Is_UInt32 );
    AFALSE( unsigned long long, Is_Int64 );
    ATRUE( unsigned long long, Is_UInt64 ); //true
    ATRUE( unsigned long long, Is_Integer ); //true
    AFALSE( unsigned long long, Is_Float );
    AFALSE( unsigned long long, Is_Double );
    AFALSE( unsigned long long, Is_LongDouble );
    AFALSE( unsigned long long, Is_Decimal );
    ATRUE( unsigned long long, Is_Premitive ); //true
    AFALSE( unsigned long long, Is_String );
    AFALSE( unsigned long long, Is_Vector );
    AFALSE( unsigned long long, Is_Object );

#elif __WORDSIZE == 32

    AFALSE( long, Is_Char );
    AFALSE( long, Is_Bool );
    AFALSE( long, Is_Int8 );
    AFALSE( long, Is_UInt8 );
    AFALSE( long, Is_Int16 );
    AFALSE( long, Is_UInt16 );
    ATRUE( long, Is_Int32 ); //true
    AFALSE( long, Is_UInt32 );
    AFALSE( long, Is_Int64 );
    AFALSE( long, Is_UInt64 );
    ATRUE( long, Is_Integer ); //true
    AFALSE( long, Is_Float );
    AFALSE( long, Is_Double );
    AFALSE( long, Is_LongDouble );
    AFALSE( long, Is_Decimal );
    ATRUE( long, Is_Premitive ); //true
    AFALSE( long, Is_String );
    AFALSE( long, Is_Vector );
    AFALSE( long, Is_Object );

    AFALSE( unsigned long, Is_Char );
    AFALSE( unsigned long, Is_Bool );
    AFALSE( unsigned long, Is_Int8 );
    AFALSE( unsigned long, Is_UInt8 );
    AFALSE( unsigned long, Is_Int16 );
    AFALSE( unsigned long, Is_UInt16 );
    AFALSE( unsigned long, Is_Int32 );
    ATRUE( unsigned long, Is_UInt32 ); //true
    AFALSE( unsigned long, Is_Int64 );
    AFALSE( unsigned long, Is_UInt64 );
    ATRUE( unsigned long, Is_Integer ); //true
    AFALSE( unsigned long, Is_Float );
    AFALSE( unsigned long, Is_Double );
    AFALSE( unsigned long, Is_LongDouble );
    AFALSE( unsigned long, Is_Decimal );
    ATRUE( unsigned long, Is_Premitive ); //true
    AFALSE( unsigned long, Is_String );
    AFALSE( unsigned long, Is_Vector );
    AFALSE( unsigned long long, Is_Object );

#endif
}

TEST( TypeTraitsTest, FloatTest )
{
    // type = float
    AFALSE( float, Is_Char );
    AFALSE( float, Is_Bool );
    AFALSE( float, Is_Int8 );
    AFALSE( float, Is_UInt8 );
    AFALSE( float, Is_Int16 );
    AFALSE( float, Is_UInt16 );
    AFALSE( float, Is_Int32 );
    AFALSE( float, Is_UInt32 );
    AFALSE( float, Is_Int64 );
    AFALSE( float, Is_UInt64 );
    AFALSE( float, Is_Integer );
    ATRUE( float, Is_Float ); //true
    AFALSE( float, Is_Double );
    AFALSE( float, Is_LongDouble );
    ATRUE( float, Is_Decimal ); //true
    ATRUE( float, Is_Premitive ); //true
    AFALSE( float, Is_String );
    AFALSE( float, Is_Vector );
    AFALSE( float, Is_Object );
}

TEST( TypeTraitsTest, DoubleTest )
{
    // type = double
    AFALSE( double, Is_Char );
    AFALSE( double, Is_Bool );
    AFALSE( double, Is_Int8 );
    AFALSE( double, Is_UInt8 );
    AFALSE( double, Is_Int16 );
    AFALSE( double, Is_UInt16 );
    AFALSE( double, Is_Int32 );
    AFALSE( double, Is_UInt32 );
    AFALSE( double, Is_Int64 );
    AFALSE( double, Is_UInt64 );
    AFALSE( double, Is_Integer );
    AFALSE( double, Is_Float );
    ATRUE( double, Is_Double ); //true
    AFALSE( double, Is_LongDouble );
    ATRUE( double, Is_Decimal ); //true
    ATRUE( double, Is_Premitive ); //true
    AFALSE( double, Is_String );
    AFALSE( double, Is_Vector );
    AFALSE( double, Is_Object );
}

TEST( TypeTraitsTest, LongDoubleTest )
{
    // type = long double
    AFALSE( long double, Is_Char );
    AFALSE( long double, Is_Bool );
    AFALSE( long double, Is_Int8 );
    AFALSE( long double, Is_UInt8 );
    AFALSE( long double, Is_Int16 );
    AFALSE( long double, Is_UInt16 );
    AFALSE( long double, Is_Int32 );
    AFALSE( long double, Is_UInt32 );
    AFALSE( long double, Is_Int64 );
    AFALSE( long double, Is_UInt64 );
    AFALSE( long double, Is_Integer );
    AFALSE( long double, Is_Float );
    AFALSE( long double, Is_Double );
    ATRUE( long double, Is_LongDouble ); //true
    ATRUE( long double, Is_Decimal ); //true
    ATRUE( long double, Is_Premitive ); //true
    AFALSE( long double, Is_String );
    AFALSE( long double, Is_Vector );
    AFALSE( long double, Is_Object );
}

TEST( TypeTraitsTest, StringTest )
{
    // type = std::string
    AFALSE( std::string, Is_Char );
    AFALSE( std::string, Is_Bool );
    AFALSE( std::string, Is_Int8 );
    AFALSE( std::string, Is_UInt8 );
    AFALSE( std::string, Is_Int16 );
    AFALSE( std::string, Is_UInt16 );
    AFALSE( std::string, Is_Int32 );
    AFALSE( std::string, Is_UInt32 );
    AFALSE( std::string, Is_Int64 );
    AFALSE( std::string, Is_UInt64 );
    AFALSE( std::string, Is_Integer );
    AFALSE( std::string, Is_Float );
    AFALSE( std::string, Is_Double );
    AFALSE( std::string, Is_LongDouble );
    AFALSE( std::string, Is_Decimal );
    ATRUE( std::string, Is_Premitive ); //true
    ATRUE( std::string, Is_String ); //true
    AFALSE( std::string, Is_Vector );
    AFALSE( std::string, Is_Object ); //false since std::string has been treaded as primitive
}

TEST( TypeTraitsTest, VectorTest )
{
    //TODO: Not implemented
}

TEST( TypeTraitsTest, ObjectTest )
{
    //TODO: Not implemented
}


} //namespace JsonTest
