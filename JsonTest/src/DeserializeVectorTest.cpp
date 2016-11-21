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
#include <vector>


// test of deserialization of std::vector
namespace JsonTest
{
namespace TestDeserializer
{
using namespace web;
using namespace std;

class DeserializeVectorTest : public ::testing::Test
{
public:
    std::vector<string> m_names;
    std::vector<string*> *m_emails;
    std::vector<const double*> *m_scores;
    std::vector<const char*> **m_cityes;
    std::vector<const int*> m_ranks;


    void DeleteEmails()
    {
        for ( auto &p : *m_emails )
        {
            delete p;
        }
        delete m_emails;
    }

    void DeleteScores()
    {
        for ( auto &p : *m_scores )
        {
            delete p;
        }
        delete m_scores;
    }

    void DeleteCities()
    {
        for ( auto &p : **m_cityes )
        {
            delete p;
        }
        delete *m_cityes;
        delete m_cityes;
    }

    void DeleteRank()
    {
        for ( auto &p : m_ranks )
        {
            delete p;
        }
    }

    void VerifyNames( const json::value &jval )
    {
        ASSERT_TRUE( jval.as_array().size() == m_names.size() );
        auto itr = m_names.begin();
        for ( auto &item : jval.as_array() )
        {
            ASSERT_TRUE( item.as_string().compare( *itr ) == 0 );
            ++itr;
        }
    }

    void VerifyEmails( const json::value &jval )
    {
        ASSERT_TRUE( jval.as_array().size() == m_emails->size() );
        auto itr = m_emails->begin();
        for ( auto &item : jval.as_array() )
        {
            ASSERT_TRUE( item.as_string().compare( **itr ) == 0 );
            ++itr;
        }
    }

    void VerifyScores( const json::value &jval )
    {
        ASSERT_TRUE( jval.as_array().size() == m_scores->size() );
        auto itr = m_scores->begin();
        for ( auto &item : jval.as_array() )
        {
            ASSERT_DOUBLE_EQ( item.as_double(), **itr );
            ++itr;
        }
    }

    void VerifyCities( const json::value &jval )
    {
        ASSERT_TRUE( jval.as_array().size() == ( *m_cityes )->size() );
        auto itr = ( *m_cityes )->begin();
        for ( auto &item : jval.as_array() )
        {
            ASSERT_TRUE( item.as_string().compare( U( const_cast<char*>( *itr ) ) ) == 0 );
            ++itr;
        }
    }

    void VerifyRanks( const json::value &jval )
    {
        ASSERT_TRUE( jval.as_array().size() == m_ranks.size() );
        auto itr = m_ranks.begin();
        for ( auto &item : jval.as_array() )
        {
            ASSERT_EQ( item.as_integer(), **itr );
            ++itr;
        }
    }
};

TEST_F( DeserializeVectorTest, TestNames )
{
    json::value jarray = json::value::array();
    json::array &arr = jarray.as_array();
    arr[0] = json::value( U( "Rezaul Karim" ) );
    arr[1] = json::value( U( "Rezaul Johny" ) );
    arr[2] = json::value( U( "Rezaul Karim Johny" ) );

    Json::FromJson( m_names, jarray );
    VerifyNames( jarray );
}


TEST_F( DeserializeVectorTest, TestEmails )
{
    json::value jarray = json::value::array();
    json::array &arr = jarray.as_array();
    arr[0] = json::value( U( "rezaul1@domain1.com" ) );
    arr[1] = json::value( U( "rezaul2@domain2.com" ) );
    arr[2] = json::value( U( "rezaul3@domain3.com" ) );

    Json::FromJson( &m_emails, jarray );
    VerifyEmails( jarray );
    DeleteEmails();
}

TEST_F( DeserializeVectorTest, TestScores )
{
    json::value jarray = json::value::array();
    json::array &arr = jarray.as_array();
    arr[0] = json::value( 11.56 );
    arr[1] = json::value( 12.65 );
    arr[2] = json::value( 15.015 );

    Json::FromJson( &m_scores, jarray );
    VerifyScores( jarray );
    DeleteScores();
}

TEST_F( DeserializeVectorTest, TestCities )
{
    json::value jarray = json::value::array();
    json::array &arr = jarray.as_array();
    arr[0] = json::value( U( "New york" ) );
    arr[1] = json::value( U( "Dhaka" ) );
    arr[2] = json::value( U( "London" ) );

    m_cityes = new std::vector<const char*>*();
    Json::FromJson( m_cityes, jarray );
    VerifyCities( jarray );
    DeleteCities();
}

TEST_F( DeserializeVectorTest, TestRanks )
{
    json::value jarray = json::value::array();
    json::array &arr = jarray.as_array();
    arr[0] = json::value( 22 );
    arr[1] = json::value( 32 );
    arr[2] = json::value( 42 );

    Json::FromJson( m_ranks, jarray );
    VerifyRanks( jarray );
    DeleteRank();
}

}
}
