cmake_minimum_required(VERSION 2.6)

message("Executing CipherTest::CMakeLists.txt to build target ${LIB_CIPHER_TEST}")

project(${LIB_CIPHER_TEST} CXX)

# setting header and source file location
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# including header files for this target
include_directories(${PROJECT_INCLUDE_DIR})

#include header foles of gtest
include_directories(${GTEST_INCLUDE_DIRS})

# include libcipher header files
include_directories(${LIB_CIPHER_INCLUDE_DIR})

# include libcmarshal header files
include_directories(${LIB_COMMON_INCLUDE_DIR})


# including source files
set(CIPHER_TEST_SRCS
        ${PROJECT_SOURCE_DIR}/main.cpp
        ${PROJECT_SOURCE_DIR}/SimpleRandomGenerator.cpp
        )


# creating JonTest target
add_executable(${PROJECT_NAME} ${CIPHER_TEST_SRCS})

# linking libcmarshal library as dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CIPHER})

# linking libcommon library as dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_LOGFIG})

# linking libcommon library as dependencies
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_COMMON})

#target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_HTTP})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY})
#target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_DBO})
#target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_PG_SQL})

target_link_libraries(${PROJECT_NAME} PUBLIC /usr/lib/x86_64-linux-gnu/libssl.a)
target_link_libraries(${PROJECT_NAME} PUBLIC /usr/lib/x86_64-linux-gnu/libcrypto.a)

# link goole test and pthread
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} boost_thread)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} boost_system)
target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} boost_random)


target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)
