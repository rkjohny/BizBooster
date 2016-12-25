cmake_minimum_required(VERSION 2.6)

message("Executing DBO::CMakeLists.txt")

project(${LIB_DBO} CXX)

# stting the heared and source files path required by libcommon target
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# exposing the header location to beincluded by other targets
set(LIB_DBO_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_DBO_INCLUDE_DIR ${LIB_DBO_INCLUDE_DIR} PARENT_SCOPE)

message("LIB_DBO_INCLUDE_DIR = ${LIB_DBO_INCLUDE_DIR}")

if (TARGET ${PROJECT_NAME})
    message("libdbo is already defined")
else ()
    message("Biulding libdbo...")
    # including heared files
    include_directories(${LIB_DBO_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})
    message("LIB_COMMON_INCLUDE_DIR = ${LIB_COMMON_INCLUDE_DIR}")

    #including libjson include dir
    include_directories(${LIB_JSON_INCLUDE_DIR})

    #including liblcrypto include dirctories
    include_directories(${LIB_LCRYPTO_INCLUDE_DIR})

    #including libfio include directory
    include_directories(${LIB_FIO_INCLUDE_DIR})

    file(GLOB LIB_DBO_HEADERS ${LIB_DBO_INCLUDE_DIR}/*.h)
    file(GLOB LIB_DBO_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_DBO_SOURCES} ${LIB_DBO_HEADERS})

    configure_file(dbo.properties ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)
endif ()
