cmake_minimum_required(VERSION 2.6)

project(BizBooster)

message("Executing BizBooster::CMakeLists.txt")

add_compile_options(-std=c++11)
set(CMAKE_BUILD_TYPE Debug)

# setting the output path
#TODO: how to get the path from where cmake commade was given without hard coding build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


# list of all projects
set(APP_NAME bizbooster)
set(LIB_JSON json)
set(LIB_JSON_TEST jsontester)
set(LIB_COMMON common)
set(LIB_API api)
set(SERVER server)
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

# setting search path for librraies
link_directories(${PROJECT_BINARY_DIR})

# setting search path for external librraies
#link_directories(/usr/local/lib/ /usr/lib/x86_64-linux-gnu/)


# Locate GTest
find_package(${GTEST} REQUIRED)
message("GTEST_LIBRARIES= ${GTEST_LIBRARIES}")
message("GTEST_INCLUDE_DIRS = ${GTEST_INCLUDE_DIRS}")

# find_package(Boost REQUIRED)
# message("cpprest_LIBRARIES= ${Boost_LIBRARIES}")
# message("cpprest_INCLUDE_DIRS = ${Boost_INCLUDE_DIRS}")


# Locate witty
find_library(LIB_WITTY ${WITTY} REQUIRED)
message ("LIB_WITTY = ${LIB_WITTY}")
if (NOT LIB_WITTY)
    message(FATAL_ERROR "witty library not found.")
endif()


# Locate witty http
find_library(LIB_WITTY_HTTP ${WITTY_HTTP} REQUIRED)
message ("LIB_WITTY_HTTP = ${LIB_WITTY_HTTP}")
if (NOT LIB_WITTY_HTTP)
    message(FATAL_ERROR "wthttp library not found.")
endif()


# Locate witty fcgi
find_library(LIB_WITTY_FCGI ${WITTY_FCGI} REQUIRED)
message ("LIB_WITTY_FCGI = ${LIB_WITTY_FCGI}")
if (NOT LIB_WITTY_FCGI)
    message(FATAL_ERROR "wtfcgi library not found.")
endif()

# Locate cpprest
find_library(LIB_CPP_REST ${CPPREST} REQUIRED)
message ("LIB_CPP_REST = ${LIB_CPP_REST}")
if (NOT LIB_CPP_REST)
    message(FATAL_ERROR "cpprest library not found.")
endif()

# Locate libboost_system
find_library(LIB_BOOST ${BOOST} REQUIRED)
message ("LIB_BOOST = ${LIB_BOOST}")
if (NOT LIB_BOOST)
    message(FATAL_ERROR "boost librray not found.")
endif()

# Locate libssl
find_library(LIB_SSL ${SSL} REQUIRED)
message ("LIB_SSL = ${LIB_SSL}")
if (NOT LIB_SSL)
    message(FATAL_ERROR "libssl librray not found.")
endif()

# Locate libcrypyo
find_library(LIB_CRYPTO ${CRYPTO} REQUIRED)
message ("LIB_CRYPTO = ${LIB_CRYPTO}")
if (NOT LIB_CRYPTO)
    message(FATAL_ERROR "libcrypto librray not found.")
endif()


# Locate libcrypyo
find_library(LIB_CRYPT ${CRYPT} REQUIRED)
message ("LIB_CRYPT = ${LIB_CRYPT}")
if (NOT LIB_CRYPT)
    message(FATAL_ERROR "libcrypt librray not found.")
endif()

# add Json, common and Api first beacuse they will export the librray header locations which will be used by JsonTest, Server and Client
add_subdirectory(Json)
add_subdirectory(JsonTest)
add_subdirectory(Common)
add_subdirectory(Api)
add_subdirectory(Server)
add_subdirectory(Client)


# setting linking dependices explecitely
# add_dependencies(JsonTest Json)

# installing tagrget BizBooster
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/local/bin)
