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

#ifndef DATE_TIME_UTILS_H
#define DATE_TIME_UTILS_H

#include <string>

#include "AppDef.h"

namespace Common {
    using namespace std;

    class DateTimeUtils {
    private:
        MAKE_STATIC(DateTimeUtils);

    public:
        static string GetTimeStamp();
    };

} /* namespace Common */

#endif /* DATE_TIME_UTILS_H */
