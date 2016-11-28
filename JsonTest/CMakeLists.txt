cmake_minimum_required(VERSION 2.6)

message("Executing JsonTest::CMakeLists.txt to build target ${LIB_JSON_TEST}")

project(${LIB_JSON_TEST} CXX)

# setting header and source file location
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# including header files for this target
include_directories(${PROJECT_INCLUDE_DIR})
message("JSON_TEST_INCCUDE_DIR = ${PROJECT_INCLUDE_DIR}")

#include header foles of gtest
include_directories(${GTEST_INCLUDE_DIRS})

# include libJson header files
include_directories(${LIB_JSON_INCLUDE_DIR})
message("LIB_JSON_INCLUDE_DIR = ${LIB_JSON_INCLUDE_DIR}")

# including source files
set(JSON_TEST_SRCS
        ${PROJECT_INCLUDE_DIR}/TestSerializableBase.h
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/EmptyClassTest.cpp
        ${PROJECT_SOURCE_DIR}/TypeTraitsTest.cpp
        ${PROJECT_SOURCE_DIR}/SerializePremitiveTest.cpp
        ${PROJECT_SOURCE_DIR}/SerializeVectorTest.cpp
        ${PROJECT_SOURCE_DIR}/SerializeConstantTest.cpp
        ${PROJECT_SOURCE_DIR}/SerializeObjectTest.cpp
        ${PROJECT_SOURCE_DIR}/SeializeNestedObjecTest.cpp
        ${PROJECT_SOURCE_DIR}/SerializeDrivedClassTest.cpp
        ${PROJECT_SOURCE_DIR}/DeserializePrimitiveTest.cpp
        ${PROJECT_SOURCE_DIR}/DeserializeObjectTest.cpp
        ${PROJECT_SOURCE_DIR}/DeserializePOD.cpp
        ${PROJECT_SOURCE_DIR}/DeserializeVectorTest.cpp
        ${PROJECT_SOURCE_DIR}/DeserializeDrivedClassTest.cpp
        ${PROJECT_SOURCE_DIR}/SerializeDoublePointerTest.cpp
        ${PROJECT_SOURCE_DIR}/DeserializeRvalueReferenceTest.cpp)


# creating JonTest target
add_executable(${PROJECT_NAME} ${JSON_TEST_SRCS})

# linking libJson library as dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_JSON})

# linking libcommon library as dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_COMMON})

# linking imported libcpprest library as dependencies
#target_link_libraries(JsonUnitTest PUBLIC /usr/local/lib/libcpprest.so)
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CPP_REST})

# link goole test and pthread
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
