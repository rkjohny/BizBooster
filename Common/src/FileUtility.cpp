/*
 * FileUtility.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#include "FileUtility.h"
#include "StringUtility.h"
#include "AppConstant.h"

namespace Common {

void FileUtility::SplitPath(vector< string >& listPath, const string& absulateFileName)
{
    StringUtility::Tokenize(listPath, absulateFileName, PATH_SEPARATOR);
}

string FileUtility::GetNameWithoutType(const string& absulateFileName)
{
    string file = "";
    auto listPath = vector< string >();

    StringUtility::Tokenize(listPath, absulateFileName, PATH_SEPARATOR);
    if (listPath.size() > 0) {
        file = listPath[ listPath.size() - 1 ];
    }

    listPath.clear();
    StringUtility::Tokenize(listPath, string(file), FILE_TYPE_SEPERATOR);

    if (listPath.size() > 1) {
        file = "";
        for (auto& str : listPath) {
            file += str;
        }
    }
    return file;
}

} /* namespace Common */
