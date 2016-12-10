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

#include "DateTimeUtils.h"
#include <time.h>

namespace Common {

string DateTimeUtils::GetTimeStamp()
{
    time_t now;
    struct tm tstruct;
    char buf[ 80 ];

    now = time(0);

#ifdef WIN32
    localtime_s(&tstruct, &now);
#else
    localtime_r(&now, &tstruct);
#endif

    // Reference: http://en.cppreference.com/w/cpp/chrono/c/strftime
    //strftime(buf, sizeof (buf), "%Y-%m-%d %I:%M:%S %p", &tstruct);
    strftime(buf, sizeof (buf), "%Y-%m-%d %H:%M:%S", &tstruct);

    return string(buf);
}

} /* namespace Common */
