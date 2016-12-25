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

#ifndef APP_CONGIF_H
#define APP_CONGIF_H

#if defined(WIN32) || defined(_WIN32) || defined (__CYGWIN__)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

#define PAIR_SEPERATOR "="

#define FILE_TYPE_SEPERATOR "."

#define JSON_API U("@api")
#define JSON_DATA U("@data")

#define USE_C_FUNCTION 1

#define FL __FILE__
#define LN __LINE__

#define APP_LOGGER "app.logger"

#define NON_COPY_NON_MOVE_ABLE(TYPE) \
        TYPE(TYPE&) = delete; \
        TYPE& operator=(TYPE&) = delete; \
        TYPE(TYPE&&) = delete; \
        TYPE& operator=(TYPE&&) = delete;

#define MAKE_STATIC(TYPE) \
    TYPE() = delete; \
    ~TYPE() = delete;

#endif //APP_CONGIF_H
