cmake_minimum_required(VERSION 2.6)

message("Executing Common::CMakeLists.txt")

project(${LIB_COMMON} CXX)

# stting the heared and source files path required by libcommon target
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# exposing the header location to beincluded by other targets
set(LIB_COMMON_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_COMMON_INCLUDE_DIR ${LIB_COMMON_INCLUDE_DIR} PARENT_SCOPE)

message("LIB_COMMON_INCLUDE_DIR = ${LIB_COMMON_INCLUDE_DIR}")

if(TARGET ${PROJECT_NAME})
    message("libcommon is already defined")
else()
    message("Biulding libcommon...")
    # including heared files
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    file(GLOB LIB_COMMON_HEADERS ${LIB_COMMON_INCLUDE_DIR}/*.h)
    file(GLOB LIB_COMMON_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_COMMON_SOURCES} ${LIB_COMMON_HEADERS})
endif()
