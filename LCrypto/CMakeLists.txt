cmake_minimum_required(VERSION 2.6)

message("Executing LCrypto::CMakeLists.txt")

project(${LIB_LCRYPTO} CXX)

# stting the heared and source files path required by libcommon target
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)


# exposing the header location to beincluded by other targets
set(LIB_LCRYPTO_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_LCRYPTO_INCLUDE_DIR ${LIB_LCRYPTO_INCLUDE_DIR} PARENT_SCOPE)

message("LIB_LCRYPTO_INCLUDE_DIR = ${LIB_LCRYPTO_INCLUDE_DIR}")

if (TARGET ${PROJECT_NAME})
    message("liblcrypto is already defined")
else ()
    message("Biulding liblcrypto...")
    # including heared files
    include_directories(${LIB_LCRYPTO_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    #including libfio include directory
    include_directories(${LIB_FIO_INCLUDE_DIR})


    file(GLOB LIB_LCRYPTO_HEADERS ${LIB_LCRYPTO_INCLUDE_DIR}/*.h)
    file(GLOB LIB_LCRYPTO_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_LCRYPTO_SOURCES} ${LIB_LCRYPTO_HEADERS})
endif ()
