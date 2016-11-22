/*
 * FileUtility.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#ifndef FILEUTILITY_H_
#define FILEUTILITY_H_

#include <string>
#include <vector>

namespace Common {
using namespace std;

class FileUtility
{
private:
    FileUtility() = delete;
    FileUtility( const FileUtility& ) = delete;
    FileUtility& operator=( const FileUtility& ) = delete;
    ~FileUtility() = delete;

public:
    static void SplitPath( vector< string >& listName, const string& absulateFileName );
    static string GetNameWithoutType( const string& absulateFileName );
};

} /* namespace Common */

#endif /* FILEUTILITY_H_ */
