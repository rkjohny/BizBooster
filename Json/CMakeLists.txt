cmake_minimum_required(VERSION 2.6)

message("Executing Json::CMakeLists.txt to build target ${LIB_JSON}")

project(${LIB_JSON} CXX)

# stting the heared and source files path required by libJson target
set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# exposing the header location to beincluded by other targets
set(LIB_JSON_INCLUDE_DIR ${PROJECT_INCLUDE_DIR})
set(LIB_JSON_INCLUDE_DIR ${LIB_JSON_INCLUDE_DIR} PARENT_SCOPE)

# building target
if(TARGET ${PROJECT_NAME})
    message("libJson is already defined")
else()
    message("Biulding libJson...")

    # including heared files
    include_directories(${LIB_JSON_INCLUDE_DIR})

    file(GLOB LIB_JSON_HEADERS ${LIB_JSON_INCLUDE_DIR}/*.h)
    file(GLOB LIB_JSON_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target libJson
    add_library(${PROJECT_NAME} STATIC ${LIB_JSON_SOURCES} ${LIB_JSON_HEADERS})

    # inslatting libJson
    # install(DIRECTORY include/ DESTINATION /usr/local/include/BizBooser/Json/)
    # install(FILES include/ DESTINATION /usr/local/include/BizBooser/Json/)
endif()
