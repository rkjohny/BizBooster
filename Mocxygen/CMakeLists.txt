cmake_minimum_required(VERSION 2.6)

message("Executing Mocxygen::CMakeLists.txt")

project(${LIB_BIZ_BOOSTER_API} CXX)

# stting the heared and source files path required by libcommon target
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# exposing the header location to beincluded by other targets
set(LIB_MOCXYGEN_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_MOCXYGEN_INCLUDE_DIR ${LIB_MOCXYGEN_INCLUDE_DIR} PARENT_SCOPE)

message("LIB_MOCXYGEN_INCLUDE_DIR = ${LIB_MOCXYGEN_INCLUDE_DIR}")

if (TARGET ${PROJECT_NAME})
    message("libmocxygen is already defined")
else ()
    message("Biulding libmocxygen...")
    # including heared files
    include_directories(${LIB_MOCXYGEN_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    #including libjson include directory
    include_directories(${LIB_CMARSHAL_INCLUDE_DIR})

    #including libjdbo include directory
    include_directories(${LIB_CRUXDB_INCLUDE_DIR})

    #including libfio include directory
    include_directories(${LIB_LOGFIG_INCLUDE_DIR})

    # including heared files
    include_directories(${LIB_CIPHER_INCLUDE_DIR})

    message("LIB_COMMON_INCLUDE_DIR = ${LIB_COMMON_INCLUDE_DIR}")

    file(GLOB LIB_MOCXYGEN_HEADERS ${LIB_MOCXYGEN_INCLUDE_DIR}/*.h)
    file(GLOB LIB_MOCXYGEN_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_MOCXYGEN_SOURCES} ${LIB_MOCXYGEN_HEADERS})
endif ()
