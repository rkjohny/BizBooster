cmake_minimum_required(VERSION 2.6)

project(BizBooster)

message("Executing BizBooster::CMakeLists.txt")

add_compile_options(-c -O1 -g3 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-write-strings -Wno-unused-local-typedefs -std=c++1z)
set(CMAKE_BUILD_TYPE Debug)


# setting the output path
#TODO: how to get the path from where cmake commade was given without hard coding build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/Binary)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# list of all projects
# Common module
set(LIB_COMMON common)

# Logger and Config reader/writer module
set(LIB_LOGFIG logfig)
# Crypto Cpipher module
set(LIB_CIPHER cipher)
# JSON serialization module
set(LIB_CMARSHAL cmarshal)
set(LIB_CMARSHAL_TEST cmarshaltester)
# SQL DB module
set(LIB_BIZ_BOOSTER_SQLDB cruxdb)
# API module
set(LIB_BIZ_BOOSTER_API mocxygen)
# Pantoon Rest Service module
set(BIZ_BOOSTER_REST_SERVICE pantoon)
# Application module
set(BIZ_BOOSTER_APP bizbooster)


# third party library used
set(CPPREST cpprest)
set(GTEST GTest)
set(BOOST boost_system)
set(SSL ssl)
set(CRYPTO crypto)
#set(CRYPT crypt)
set(PTHREAD, pthread)
set(WITTY wtd)
set(WITTY_HTTP wthttpd)
#set(WITTY_FCGI wtfcgid)
set(WITTY_DBO wtdbod)
set(WITTY_PG_SQL wtdbopostgresd)
#set(WITTY_EXT wtext)

# setting search path for librraies
link_directories(${PROJECT_BINARY_DIR})

# setting search path for external librraies
#link_directories(/usr/local/lib/ /usr/lib/x86_64-linux-gnu/)


# Locate GTest
find_package(${GTEST} REQUIRED)
message("GTEST_LIBRARIES= ${GTEST_LIBRARIES}")
message("GTEST_INCLUDE_DIRS = ${GTEST_INCLUDE_DIRS}")

# Locate witty
find_library(LIB_WITTY ${WITTY} REQUIRED)
message ("LIB_WITTY = ${LIB_WITTY}")
if (NOT LIB_WITTY)
    message(FATAL_ERROR "libwt not found.")
endif()

# Locate witty http
find_library(LIB_WITTY_HTTP ${WITTY_HTTP} REQUIRED)
message ("LIB_WITTY_HTTP = ${LIB_WITTY_HTTP}")
if (NOT LIB_WITTY_HTTP)
    message(FATAL_ERROR "libwthttp not found.")
endif()

# Locate witty dbo
find_library(LIB_WITTY_DBO ${WITTY_DBO} REQUIRED)
message ("LIB_WITTY_DBO = ${LIB_WITTY_DBO}")
if (NOT LIB_WITTY_DBO)
    message(FATAL_ERROR "libwtdbo not found.")
endif()

# Locate witty dbo
find_library(LIB_WITTY_PG_SQL ${WITTY_PG_SQL} REQUIRED)
message ("LIB_WITTY_PG_SQL = ${LIB_WITTY_PG_SQL}")
if (NOT LIB_WITTY_PG_SQL)
    message(FATAL_ERROR "libwtdbopostgres not found.")
endif()

# Locate witty fcgi
#find_library(LIB_WITTY_FCGI ${WITTY_FCGI} REQUIRED)
#message ("LIB_WITTY_FCGI = ${LIB_WITTY_FCGI}")
#if (NOT LIB_WITTY_FCGI)
# message(FATAL_ERROR "libwtfcgi found.")
#endif()

## Locate witty fcgi
#find_library(LIB_WITTY_EXT ${WITTY_EXT} REQUIRED)
#message ("LIB_WITTY_EXT = ${LIB_WITTY_EXT}")
#if (NOT LIB_WITTY_EXT)
#    message(FATAL_ERROR "libwtext not found.")
#endif()




# Locate cpprest
find_library(LIB_CPP_REST ${CPPREST} REQUIRED)
message ("LIB_CPP_REST = ${LIB_CPP_REST}")
if (NOT LIB_CPP_REST)
    message(FATAL_ERROR "libcpprest not found.")
endif()

# Locate libboost_system
find_library(LIB_BOOST ${BOOST} REQUIRED)
message ("LIB_BOOST = ${LIB_BOOST}")
if (NOT LIB_BOOST)
    message(FATAL_ERROR "libboost not found.")
endif()

# Locate libssl
find_library(LIB_SSL ${SSL} REQUIRED)
message ("LIB_SSL = ${LIB_SSL}")
if (NOT LIB_SSL)
    message(FATAL_ERROR "libssl not found.")
endif()

# Locate libcrypyo
find_library(LIB_CRYPTO ${CRYPTO} REQUIRED)
message ("LIB_CRYPTO = ${LIB_CRYPTO}")
if (NOT LIB_CRYPTO)
    message(FATAL_ERROR "libcrypto not found.")
endif()


# Locate libcrypyo
#find_library(LIB_CRYPT ${CRYPT} REQUIRED)
#message ("LIB_CRYPT = ${LIB_CRYPT}")
#if (NOT LIB_CRYPT)
#    message(FATAL_ERROR "libcrypt not found.")
#endif()

# Locate libpthread
#find_library(LIB_PTHREAD ${PTHREAD} REQUIRED)
#message ("LIB_PTHREAD = ${LIB_PTHREAD}")
#if (NOT LIB_PTHREAD)
#    message(FATAL_ERROR "libpthread not found.")
#endif()


# add common, Cmarshal, Cruxdb, and Mocxygen first beacuse they will export the librray header locations which will be used by CmarshalTest, Server and Client
#include Common first, before Cmarshal
add_subdirectory(Common)
add_subdirectory(Logfig)
add_subdirectory(Cipher)
add_subdirectory(Cmarshal)
add_subdirectory(CmarshalTest)
add_subdirectory(Cruxdb)
add_subdirectory(Mocxygen)
add_subdirectory(Pantoon)
add_subdirectory(App)



# setting linking dependices explecitely
# add_dependencies(CmarshalTest Cmarshal)

# installing tagrget BizBooster
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/local/bin)
