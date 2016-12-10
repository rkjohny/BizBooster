/**
 * Author: Rezaul Karim
 * Email: rkjohny@gmail.com
 *
 * Copyright (C) 20016 Rezaul Karim (rkjohny@gmail.com) all rights reserved.
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

namespace Common {
    using namespace std;

    class FileUtility {
    private:
        FileUtility() = delete;
        FileUtility(const FileUtility&) = delete;
        FileUtility& operator=(const FileUtility&) = delete;
        ~FileUtility() = delete;

    public:
        static void SplitPath(vector< string >& listName, const string& absulateFileName);
        static string GetNameWithoutType(const string&& absulateFileName);
    };

} /* namespace Common */

#endif /* FILE_UTILITY_H */
