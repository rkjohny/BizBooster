/*
 * FileUtility.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#include "FileUtility.h"
#include "StringUtility.h"
#include "AppConfig.h"

namespace Common {

void FileUtility::SplitPath(vector< string >& listPath, const string& absulateFileName)
{
    StringUtility::Tokenize(listPath, absulateFileName, PATH_SEPARATOR);
}

string FileUtility::GetNameWithoutType(const string&& absulateFileName)
{
    string file = "";
    auto listPath = vector< string >();

    StringUtility::Tokenize(listPath, absulateFileName, PATH_SEPARATOR);
    if (listPath.size() > 0) {
        file = listPath[ listPath.size() - 1 ];
    }

    listPath.clear();
    StringUtility::Tokenize(listPath, file, FILE_TYPE_SEPERATOR);

#if 0
    //eliminating extension
    int ln = listPath.size();
    if (ln > 1) {
        file = "";
        for (int i = 0; i < (ln - 1); ++i) {
            if (i > 0) {
                file += FILE_TYPE_SEPERATOR;
            }
            file += listPath[i];
        }
    }
#endif
    return file;
}

} /* namespace Common */
