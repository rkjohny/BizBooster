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

#include "DateTimeUtils.h"
#include <time.h>
#include <ctime>


namespace Common {

std::string DateTimeUtils::GetTimeStamp()
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

    return std::string(buf);
}

void DateTimeUtils::GetCurrentDateTime(Wt::WDateTime &dt)
{
    std::time_t curTime = std::time(nullptr);
    dt.setTime_t(curTime);
}

void DateTimeUtils::AddDayToCurrentDateTime(Wt::WDateTime &dt, uint32_t day)
{
    std::time_t curTime = std::time(nullptr);
    
    curTime += (day * 24 * 60 * 60 * 100);
    
//    std::tm *tm_local = std::localtime(&curTime);
//    tm_local->tm_mday += day;
//    std::time_t next = std::mktime(tm_local);
//    dt.setTime_t(next);
    
    dt.setTime_t(curTime);
}

Wt::WDateTime DateTimeUtils::Now()
{
    Wt::WDateTime now;
    std::time_t curTime = std::time(nullptr);
    now.setTime_t(curTime);
    return now;
}

Wt::WDateTime DateTimeUtils::AddMscToNow(uint64_t msec)
{
    Wt::WDateTime now;
    std::time_t curTime = std::time(nullptr);
    curTime += msec;
    now.setTime_t(curTime);
    return now;
}

} /* namespace Common */
