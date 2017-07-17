cmake_minimum_required(VERSION 2.6)

message("Executing Cmarashal::CMakeLists.txt to build target ${LIB_CMARSHAL}")

project(${LIB_CMARSHAL} CXX)

# stting the heared and source files path required by libJson target
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# exposing the header location to beincluded by other targets
set(LIB_CMARSHAL_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_CMARSHAL_INCLUDE_DIR ${LIB_CMARSHAL_INCLUDE_DIR} PARENT_SCOPE)

# building target
if (TARGET ${PROJECT_NAME})
    message("libcmarshal is already defined")
else ()
    message("Biulding libcmarshal...")

    # including heared files
    include_directories(${LIB_CMARSHAL_INCLUDE_DIR})

    # including libcommon header files
    include_directories(${LIB_COMMON_INCLUDE_DIR})
    message("LIB_CMARSHAL includes libcommon include dir  = ${LIB_COMMON_INCLUDE_DIR}")

    file(GLOB LIB_CMARSHAL_HEADERS ${LIB_CMARSHAL_INCLUDE_DIR}/*.h)
    file(GLOB LIB_CMARSHAL_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_CMARSHAL_SOURCES} ${LIB_CMARSHAL_HEADERS})

    # inslatting libJson
    # install(DIRECTORY include/ DESTINATION /usr/local/include/BizBooser/Cmarshal/)
    # install(FILES include/ DESTINATION /usr/local/include/BizBooser/Cmarshal/)
endif ()
