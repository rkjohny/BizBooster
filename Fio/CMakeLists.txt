cmake_minimum_required(VERSION 2.6)

message("Executing Fio::CMakeLists.txt")

project(${LIB_FIO} CXX)

# stting the heared and source files path required by libcommon target
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# exposing the header location to beincluded by other targets
set(LIB_FIO_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_FIO_INCLUDE_DIR ${LIB_FIO_INCLUDE_DIR} PARENT_SCOPE)

message("LIB_FIO_INCLUDE_DIR = ${LIB_FIO_INCLUDE_DIR}")

if (TARGET ${PROJECT_NAME})
    message("libfio is already defined")
else ()
    message("Biulding libfio...")
    # including heared files
    include_directories(${LIB_FIO_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    file(GLOB LIB_FIO_HEADERS ${LIB_FIO_INCLUDE_DIR}/*.h)
    file(GLOB LIB_FIO_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_FIO_SOURCES} ${LIB_FIO_HEADERS})
endif ()
