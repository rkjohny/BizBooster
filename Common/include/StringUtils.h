/*
 * StringUtils.h
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#ifndef STRINGUTILS_H_
#define STRINGUTILS_H_

#include <vector>
#include <mutex>
#include <sstream>
#include <string>

namespace Common {
using namespace std;

class StringUtils
{
private:
    StringUtils() = delete;
    StringUtils( const StringUtils& ) = delete;
    StringUtils& operator=( const StringUtils& ) = delete;
    ~StringUtils() = delete;

    static string cm_newLineStr;
    static string cm_tabStr;

    class Initializer
    {
    public:
        Initializer();
    private:
        ostringstream m_ss;
    };

    static Initializer cm_initializer;

public:
    static string Trim( const string& str );

    static string ToStr( int n );

    static int ToInt( const string& s ) throw (invalid_argument);

    static void Tokenize( vector< string >& v, const string& str, const string& token, int n = 0 );

    static string GetNewLineStr();

    static string GetTabLineStr();

    static void ToLower( string& str );
};

} /* namespace Common */

#endif /* STRINGUTILS_H_ */
