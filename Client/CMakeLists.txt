cmake_minimum_required(VERSION 2.6)

message("Executing CLIENT::CMakeLists.txt")

project(${CLIENT} CXX)


if(TARGET ${PROJECT_NAME})
    message("client is already defined")
else()
    message("Biulding client...")

    # stting the heared and source files path required by libcommon target
    set (PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set (PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

    # including heared files
    include_directories(${PROJECT_INCLUDE_DIR})
    message("PROJECT_INCLUDE_DIR = ${PROJECT_INCLUDE_DIR}")

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})


    file(GLOB CLIENT_HEADERS ${PROJECT_INCLUDE_DIR}/*.h)
    file(GLOB CLIENT_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target server
    add_executable(${PROJECT_NAME} ${CLIENT_SOURCES} ${PROJECT_INCLUDE_DIR})

    # linking libcommon library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_COMMON})

    # linking third party library dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${WITTY_HTTP})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_FCGI})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_BOOST})

    configure_file(Client.ini ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)
    configure_file(lang.en_US.properties ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)
endif()
