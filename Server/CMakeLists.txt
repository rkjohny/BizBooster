cmake_minimum_required(VERSION 2.6)

message("Executing SERVER::CMakeLists.txt")

project(${SERVER} CXX)


if (TARGET ${PROJECT_NAME})
    message("server is already defined")
else ()
    message("Biulding server...")

    # stting the heared and source files path required by libcommon target
    set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

    # including heared files
    include_directories(${PROJECT_INCLUDE_DIR})
    message("PROJECT_INCLUDE_DIR = ${PROJECT_INCLUDE_DIR}")

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    # including libjson include directory
    include_directories(${LIB_JSON_INCLUDE_DIR})

    # including libjson include directory
    include_directories(${LIB_DBO_INCLUDE_DIR})

    # including libapi include directory
    include_directories(${LIB_API_INCLUDE_DIR})


    file(GLOB SERVER_HEADERS ${PROJECT_INCLUDE_DIR}/*.h)
    file(GLOB SERVER_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target server
    add_executable(${PROJECT_NAME} ${SERVER_SOURCES} ${PROJECT_INCLUDE_DIR})

    # linking libapi library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_API})

    # linking libjson library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_DBO})

    # linking libjson library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_JSON})

    # linking libcommon library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_COMMON})

    # linking third party library dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CPP_REST})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_BOOST})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_SSL})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CRYPTO})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CRYPT})

    #target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_PG_SQL})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_DBO})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_PG_SQL})

    configure_file(server.properties ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)

endif ()
