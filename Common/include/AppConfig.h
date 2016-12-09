#ifndef APPCONOSTANT_H
#define APPCONOSTANT_H

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


#define NON_COPY_ABLE(TYPE) \
        TYPE(TYPE&) = delete; \
        TYPE(TYPE&&) = delete; \

#define NON_ASSIGN_ABLE(TYPE) \
        TYPE& operator=(TYPE&) = delete; \
        TYPE& operator=(TYPE&&) = delete;

#define NON_COPY_NON_ASSIGN_ABLE(TYPE) \
        TYPE(TYPE&) = delete; \
        TYPE& operator=(TYPE&) = delete; \
        TYPE(TYPE&&) = delete; \
        TYPE& operator=(TYPE&&) = delete;


#endif
