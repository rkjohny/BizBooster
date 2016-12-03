/*
 * StringUtils.cpp
 *
 *  Created on: Oct 12, 2016
 *      Author: rezaul
 */

#include "StringUtility.h"

#define USE_C_FUNCTION 1

#if USE_C_FUNCTION
#include <string.h>
#else
#ifndef WIN32
#include <cstdio>
#include <cstring>
#endif
#endif

#include <algorithm>
#include <ctype.h>

namespace Common {

//creation of static variable,
//note that cm_newLineStr and cm_tabStr should be created before cm_initializer, the order is important
//because the constructor of cm_initializer will use these two variables
string StringUtility::cm_newLineStr;
string StringUtility::cm_tabStr;
StringUtility::Initializer StringUtility::cm_initializer;

StringUtility::Initializer::Initializer()
{
    //crates new line string
    m_ss << m_ss.widen('\n');
    StringUtility::cm_newLineStr = m_ss.str();

    //clear the buffer
    m_ss.str("");

    //create tab string
    m_ss << m_ss.widen('\t');
    StringUtility::cm_tabStr = m_ss.str();
}

string StringUtility::GetNewLineStr()
{
    return cm_newLineStr;
}

string StringUtility::GetTabLineStr()
{
    return cm_tabStr;
}

string StringUtility::Trim(const string& str)
{
    const char* p = str.c_str();
    size_t front = 0, rear = str.length();

    while (front < rear && p[ front ] == ' ') {
        ++front;
    }

    while (front < rear && p[ rear - 1 ] == ' ') {
        --rear;
    }

    return str.substr(front, rear - front);
}

string StringUtility::ToStr(int n)
{
    char s[ 50 ];
#ifdef WINT_M32

    sprintf_s(s, sizeof ( s), "%d", n);
#else

    snprintf(s, sizeof ( s), "%d", n);
#endif

    return s;
}

int StringUtility::ToInt(const string& s) throw ( invalid_argument)
{
    return stoi(s, 0, 10);
}

void StringUtility::Tokenize(vector< string >& v, const string& str, const string& token, int n)
{
    size_t len = str.length();

    if (len > 0 && n >= 0) {
        const char* t = token.c_str();
        string newStr = str; // creating a local copy
        char* p = const_cast<char*> (newStr.c_str());
        int count = 1;

#ifdef WIN32 // WINDOWS

        char* context;
        p = strtok_s(p, t, &context);

        while (p && (!n || count++ <= n)) {
            v.push_back(p);
            p = strtok_s(nullptr, t, &context);
        }
#else // LINUX
#if USE_C_FUNCTION
        // using c function strtok
        char* context;
        p = strtok_r(p, t, &context);
        while (p && (!n || count++ <= n)) {
            v.push_back(p);
            p = strtok_r(nullptr, t, &context);
        }
#else
        // using c++ function strpbrk and strspn
        char* next = nullptr;
        do {
            next = strpbrk(p, t); // find separator
            if (next) {
                v.push_back(string(p, next - p));
                next += strspn(next, t); // skip separator
            } else {
                v.push_back(string(p));
            }
            p = next;
        } while (p && *p && (!n || ++count <= n));
#endif
#endif

    }
}

void StringUtility::ToLower(string& str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
}

int StringUtility::Compare(std::string first, std::string second, bool ignore_case)
{
    if (ignore_case) {
        StringUtility::ToLower(first);
        StringUtility::ToLower(second);
    }
    return first.compare(second);
}

} /* namespace Common */
