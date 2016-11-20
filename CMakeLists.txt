cmake_minimum_required(VERSION 2.6)

project(BizBooster)

message("Executing BizBooster::CMakeLists.txt")

add_compile_options(-std=c++14)
set(CMAKE_BUILD_TYPE Debug)

# setting the output path
#TODO: how to get the path from where cmake commade wad given without hard coding build
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# list of all projects
set(APP_NAME bizbooster)
set(LIB_JSON tynyjson)
set(LIB_JSON_TEST jsontester)

# third party library used
set(LIB_CPP_REST cpprest)
set(LIB_WITTY wt)

# third party library location
if (!CPP_REST_INSTALLATION_DIR)
    set(CPP_REST_INSTALLATION_DIR /usr/local)
endif()

# add Json first beacuse it will export the librray header location which will be used by JsonTest
add_subdirectory(Json)
add_subdirectory(JsonTest)

# setting linking dependices explecitely
# add_dependencies(JsonTest Json)

# installing tagrget BizBooster
# install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION /usr/local/bin)
