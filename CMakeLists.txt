cmake_minimum_required(VERSION 2.6)

project(BizBooster)

message("Executing BizBooster::CMakeLists.txt")

add_compile_options(-std=c++1y)
set(CMAKE_BUILD_TYPE Debug)

# setting the output path
#TODO: how to get the path from where cmake commade was given without hard coding build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/binary)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# list of all projects
set(LIB_COMMON common)
set(LIB_FIO fio)
set(LIB_LCRYPTO lcrypto)
set(LIB_JSON json)
set(LIB_JSON_TEST jsontester)
set(LIB_DBO dbo)
set(LIB_API api)
set(SERVICE service)
set(WEB_APP bizbooster)
set(CLIENT client)


# third party library used
set(CPPREST cpprest)
set(GTEST GTest)
set(BOOST boost_system)
set(SSL ssl)
set(CRYPTO crypto)
set(CRYPT crypt)
set(WITTY wt)
set(WITTY_HTTP wthttp)
set(WITTY_FCGI wtfcgi)
set(WITTY_DBO wtdbo)
set(WITTY_PG_SQL wtdbopostgres)
set(WITTY_EXT wtext)

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
find_library(LIB_CRYPT ${CRYPT} REQUIRED)
message ("LIB_CRYPT = ${LIB_CRYPT}")
if (NOT LIB_CRYPT)
    message(FATAL_ERROR "libcrypt not found.")
endif()


# add common, Json, Dal, and Api first beacuse they will export the librray header locations which will be used by JsonTest, Server and Client
#include Common first, before Json
add_subdirectory(Common)
add_subdirectory(Fio)
add_subdirectory(LCrypto)
add_subdirectory(Json)
#add_subdirectory(JsonTest)
add_subdirectory(Dbo)
add_subdirectory(Api)
add_subdirectory(Service)
#add_subdirectory(App)
#add_subdirectory(Client)


# setting linking dependices explecitely
# add_dependencies(JsonTest Json)

# installing tagrget BizBooster
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/local/bin)
