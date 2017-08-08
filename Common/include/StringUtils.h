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
#include <sstream>
#include <string>

#include "AppCommonDef.h"

namespace Common {
    
    class StringUtils {
    private:
        MAKE_STATIC(StringUtils);

        static std::string cm_newLineStr;
        static std::string cm_tabStr;

        class Initializer {
        public:
            Initializer();
        private:
            std::ostringstream m_ss;
        };

        static Initializer cm_initializer;

    public:
        static void Trim(std::string& str);

        static void Tokenize(std::vector< std::string >& v, const std::string& str, const std::string& token);

        static std::string GetNewLineStr();

        static std::string GetTabLineStr();

        static void ToLower(std::string& str);
        
        static void ToUpper(std::string& str);

        static int Compare(const std::string &first, const std::string &second, bool ignore_case = false);
    };

} /* namespace Common */

#endif /* STRINGUTILS_H */
