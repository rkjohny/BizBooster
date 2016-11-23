/*
 * DateTimeUtils.cpp
 *
 *  Created on: Oct 11, 2016
 *      Author: rezaul
 */

#include "DateTimeUtils.h"
#include <time.h>

namespace Common {

string DateTimeUtils::GetTimeStamp()
{
    time_t now;
    struct tm tstruct;
    char buf[ 80 ];

    now = time( 0 );

#ifdef WIN32
    localtime_s( &tstruct, &now );
#else
    localtime_r( &now, &tstruct );
#endif

    // Reference: http://en.cppreference.com/w/cpp/chrono/c/strftime
    strftime( buf, sizeof(buf), "%Y-%m-%d %I:%M:%S %p", &tstruct );

    return string( buf );
}

} /* namespace Common */
