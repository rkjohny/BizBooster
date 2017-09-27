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

#ifndef APP_COMMON_DEF_H
#define APP_COMMON_DEF_H

//#include "SingleTon.h"
//#include "Requester.h
//#include <memory>

#if defined(WIN32) || defined(_WIN32)
#define WINDOWS
#else
#define LINUX
#endif

#if defined(WINDOWS)
#define PATH_SEPARATOR "\\"
#elif defined(LINUX)
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

#define UNUSED(x) ((void)(x))


#define NON_COPY_NON_MOVE_ABLE(TYPE) \
        TYPE(TYPE&) = delete; \
        TYPE& operator=(TYPE&) = delete; \
        TYPE(TYPE&&) = delete; \
        TYPE& operator=(TYPE&&) = delete;


#define MAKE_STATIC(TYPE) \
    TYPE() = delete; \
    ~TYPE() = delete;


#define COPY_ABLE_MOVE_ABLE(TYPE) \
        TYPE(const TYPE &orig) { \
            CopyFrom(orig); \
        } \
        TYPE(TYPE &&orig) { \
            CopyFrom(std::move(orig)); \
        } \
        TYPE(const std::shared_ptr<TYPE> &orig) { \
            CopyFrom(orig); \
        } \
        TYPE & operator=(const TYPE &orig) { \
             CopyFrom(orig); \
             return *this; \
        } \
        TYPE & operator=(TYPE &&orig) { \
            CopyFrom(std::move(orig)); \
            return *this; \
        } \
        TYPE & operator=(const std::shared_ptr<TYPE> &orig) { \
            CopyFrom(orig); \
            return *this; \
        } \
        void CopyFrom(const std::shared_ptr<TYPE>& orig) { \
            CopyFrom(*orig); \
        } \
        virtual void CopyFrom(const TYPE &orig); \
        virtual void CopyFrom(const TYPE &&orig);



#define SERIALIZEABLE(TYPE) \
    TYPE() = default; \
    COPY_ABLE_MOVE_ABLE(TYPE)

#define API_INPUT(TYPE) \
    TYPE() = default; \
    COPY_ABLE_MOVE_ABLE(TYPE) \
    std::string ToString() const override; \
    std::string Name() const override; \
    std::shared_ptr<AbstractBaseOutput> Process(std::shared_ptr<Cruxdb::Requester> requester, std::shared_ptr<AbstractBaseInput> input) override;

#define API_OUTPUT(TYPE) \
    TYPE() = default; \
    COPY_ABLE_MOVE_ABLE(TYPE) \
    std::string ToString() const override; \
    std::string Name() const override;


#define API_HELPER(TYPE) \
    NON_COPY_NON_MOVE_ABLE(TYPE)

#define MAKE_SINGLE_TON(TYPE) \
    friend class Common::SingleTon<TYPE>; \
    NON_COPY_NON_MOVE_ABLE(TYPE)

#endif //APP_COMMON_DEF_H
