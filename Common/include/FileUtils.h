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

#ifndef FILE_UTILITY_H
#define FILE_UTILITY_H

#include <string>
#include <vector>

#include "AppCommonDef.h"

namespace Common {
    class FileUtils {
    private:
        MAKE_STATIC(FileUtils);

    public:
        static void SplitPath(std::vector< std::string >& listName, const std::string& absulateFileName);
        static std::string GetName(const std::string &absulateFileName);
    };

} /* namespace Common */

#endif /* FILE_UTILITY_H */
