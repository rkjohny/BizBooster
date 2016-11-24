cmake_minimum_required(VERSION 2.6)

message("Executing API::CMakeLists.txt")

project(${LIB_API} CXX)

# stting the heared and source files path required by libcommon target
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# exposing the header location to beincluded by other targets
set(LIB_API_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_API_INCLUDE_DIR ${LIB_API_INCLUDE_DIR} PARENT_SCOPE)

message("LIB_API_INCLUDE_DIR = ${LIB_API_INCLUDE_DIR}")

if(TARGET ${PROJECT_NAME})
    message("libapi is already defined")
else()
    message("Biulding libapi...")
    # including heared files
    include_directories(${LIB_API_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    #including libjson include directory
    include_directories(${LIB_JSON_INCLUDE_DIR})

    message("LIB_COMMON_INCLUDE_DIR = ${LIB_COMMON_INCLUDE_DIR}")

    file(GLOB LIB_API_HEADERS ${LIB_API_INCLUDE_DIR}/*.h)
    file(GLOB LIB_API_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_API_SOURCES} ${LIB_API_HEADERS})
endif()
