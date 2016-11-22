/*
 * DateTimeUtils.h
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#ifndef DATETIMEUTILS_H_
#define DATETIMEUTILS_H_

#include <string>

namespace Common {
using namespace std;

class DateTimeUtils
{
private:
    DateTimeUtils() = delete;
    DateTimeUtils( const DateTimeUtils& ) = delete;
    DateTimeUtils& operator =( DateTimeUtils& ) = delete;
    ~DateTimeUtils() = delete;

public:
    static string GetTimeStamp();
};

} /* namespace Common */

#endif /* DATETIMEUTILS_H_ */
