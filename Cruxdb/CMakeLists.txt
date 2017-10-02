cmake_minimum_required(VERSION 2.6)

message("Executing Cruxdb::CMakeLists.txt")

project(${LIB_BIZ_BOOSTER_SQLDB} CXX)

# stting the heared and source files path required by libcommon target
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# exposing the header location to beincluded by other targets
set(LIB_CRUXDB_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_CRUXDB_INCLUDE_DIR ${LIB_CRUXDB_INCLUDE_DIR} PARENT_SCOPE)

message("LIB_CRUXDB_INCLUDE_DIR = ${LIB_CRUXDB_INCLUDE_DIR}")

if (TARGET ${PROJECT_NAME})
    message("libcruxdb is already defined")
else ()
    message("Biulding libcrusdb...")
    # including heared files
    include_directories(${LIB_CRUXDB_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})
    message("LIB_COMMON_INCLUDE_DIR = ${LIB_COMMON_INCLUDE_DIR}")

    #including libjson include dir
    include_directories(${LIB_CMARSHAL_INCLUDE_DIR})

    #including liblcrypto include dirctories
    include_directories(${LIB_CIPHER_INCLUDE_DIR})

    #including libfio include directory
    include_directories(${LIB_LOGFIG_INCLUDE_DIR})


    file(GLOB LIB_CRUXDB_HEADERS ${LIB_CRUXDB_INCLUDE_DIR}/*.h)
    file(GLOB LIB_CRUXDB_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_CRUXDB_SOURCES} ${LIB_CRUXDB_HEADERS})

    configure_file(cruxdb.properties ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)
endif ()
