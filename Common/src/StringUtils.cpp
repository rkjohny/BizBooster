/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 2017 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
 *
 * The information contained here-in is the property of Rezaul Karim and is not to be
 * disclosed or used without prior written permission of Rezaul Karim. This copyright
 * extends to all media in which this information may be preserved including
 * magnetic storage, computer print-out or visual display.
 */

#include "StringUtils.h"
#include "AppCommonDef.h"
#include <algorithm>
#include <cstring>
#include <string>
#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>


namespace Common {

//creation of static variable,
//note that cm_newLineStr and cm_tabStr should be created before cm_initializer, the order is important
//because the constructor of cm_initializer will use these two variables
std::string StringUtils::cm_newLineStr;
std::string StringUtils::cm_tabStr;
StringUtils::Initializer StringUtils::cm_initializer;

StringUtils::Initializer::Initializer()
{
    //crates new line string
    m_ss << m_ss.widen('\n');
    StringUtils::cm_newLineStr = m_ss.str();

    //clear the buffer
    m_ss.str("");

    //create tab string
    m_ss << m_ss.widen('\t');
    StringUtils::cm_tabStr = m_ss.str();
}

std::string StringUtils::GetNewLineStr()
{
    return cm_newLineStr;
}

std::string StringUtils::GetTabLineStr()
{
    return cm_tabStr;
}

void StringUtils::Trim(std::string& str)
{
    boost::algorithm::trim_left_if(str, boost::algorithm::is_any_of("\r\n\t "));
    boost::algorithm::trim_right_if(str, boost::algorithm::is_any_of("\r\n\t "));
}

void StringUtils::Tokenize(std::vector< std::string > &v, const std::string &str, const std::string &token)
{
    boost::algorithm::split(v, str, boost::algorithm::is_any_of(token), boost::algorithm::token_compress_on );
}

void StringUtils::ToLower(std::string& str)
{
    boost::algorithm::to_lower(str);
}

void StringUtils::ToUpper(std::string& str)
{
    boost::algorithm::to_upper(str);
}

int StringUtils::Compare(const std::string &first, const std::string &second, bool ignore_case)
{
    if (ignore_case) {
        return boost::algorithm::iequals(first, second);
    }
    return boost::algorithm::equals(first, second);
}

} /* namespace Common */

