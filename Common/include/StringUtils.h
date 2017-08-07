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

#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <vector>
#include <mutex>
#include <sstream>
#include <string>

#include "AppCommonDef.h"

namespace Common {
    using namespace std;

    class StringUtils {
    private:
        MAKE_STATIC(StringUtils);

        static string cm_newLineStr;
        static string cm_tabStr;

        class Initializer {
        public:
            Initializer();
        private:
            ostringstream m_ss;
        };

        static Initializer cm_initializer;

    public:
        static string Trim(const string& str);

        static void Tokenize(vector< string >& v, const string& str, const string& token, int n = 0);

        static string GetNewLineStr();

        static string GetTabLineStr();

        static void ToLower(string& str);

        static int Compare(const std::string &first, const std::string &second, bool ignore_case = false);
    };

} /* namespace Common */

#endif /* STRINGUTILS_H */
