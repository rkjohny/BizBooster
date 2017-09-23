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

#ifndef DATE_TIME_UTILS_H
#define DATE_TIME_UTILS_H

#include <Wt/Dbo/WtSqlTraits.h>
#include <string>

#include "AppCommonDef.h"

namespace Common {
    class DateTimeUtils {
    private:
        MAKE_STATIC(DateTimeUtils);

    public:
        static std::string GetTimeStamp();

        static void GetCurrentDateTime(Wt::WDateTime &dt);
        static void AddDayToCurrentDateTime(Wt::WDateTime &dt, uint32_t day);
        
        static Wt::WDateTime Now();
        static Wt::WDateTime AddMsecToNow(uint64_t msec);
        static Wt::WDateTime AddSecToNow(uint64_t sec);
    };

} /* namespace Common */

#endif /* DATE_TIME_UTILS_H */
