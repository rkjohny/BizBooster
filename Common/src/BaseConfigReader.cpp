/*
 * TradexConfigReader.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#include <fstream>
#include "BizBooster/Common/BaseConfigReader.h"
#include "BizBooster/Common/StringUtils.h"
#include "BizBooster/Common/AppConstant.h"

namespace Common
{

BaseConfigReader::BaseConfigReader()
{
}

BaseConfigReader::~BaseConfigReader()
{
    BaseConfigReader::Dispose();
}

void BaseConfigReader::Dispose()
{
    m_mutex.lock();
    if ( !m_isDosposed )
    {
        m_properties.clear();
        m_isDosposed = true;
    }
    m_mutex.unlock();
}

void BaseConfigReader::SetFile( const string& filename ) throw ( AppException )
{
    m_mutex.lock();
    m_fileName = filename;
    LoadFile( filename );
    m_isDosposed = false;
    m_mutex.unlock();
}

void BaseConfigReader::ReloadFile() throw ( AppException )
{
    m_mutex.lock();
    LoadFile( m_fileName );
    m_isDosposed = false;
    m_mutex.unlock();
}

void BaseConfigReader::LoadFile( const string& filename ) throw ( AppException )
{
    try
    {
        ifstream infs( filename.c_str() );
        string line;
        m_properties.clear();

        try
        {
            while ( getline( infs, line ) )
            {
                line = StringUtils::Trim( line );
                if ( line.length() == 0 || line.at( 0 ) == '#' )
                {
                    continue;
                }

                size_t pos = line.find( PAIR_SEPERATOR );
                //pos must be valid index and cannot be the first and last index
                if ( pos > 0 && pos < line.size() - 1 )
                {
                    vector< string > listValue = vector< string >();
                    StringUtils::Tokenize( listValue, line, PAIR_SEPERATOR, 2 );
                    if ( listValue.size() >= 2 )
                    {
                        m_properties[ listValue[ 0 ] ] = listValue[ 1 ];
                    }
                }
            }
        }
        catch ( exception &e )
        {
            infs.close();
            throw AppException( e, ApiReturnCode::COULD_NOT_OPEN_FILE,
                                "Could not open file : " + filename );
        }
        infs.close();
    }
    catch ( exception &e )
    {
        throw AppException( e, ApiReturnCode::COULD_NOT_OPEN_FILE,
                            "Could not open file : " + filename );
    }
}

string BaseConfigReader::GetValueOf( const string& key )
{
    string value = "";
    m_mutex.lock();
    if ( !m_isDosposed )
    {
        if ( m_properties.find( key ) != m_properties.end() )
        {
            value = m_properties[ key ];
        }
    }
    m_mutex.unlock();
    return value;
}

} /* namespace Common */
