#WT_ADD_EXAMPLE(auth2.wt
#        Auth2.C
#	AuthWidget.C
#	RegistrationView.C
#	model/Session.C
#	model/User.C
#	model/UserDetailsModel.C
#)
#TARGET_LINK_LIBRARIES(auth2.wt wtdbo wtdbosqlite3)
#INCLUDE_DIRECTORIES(${WT_SOURCE_DIR}/src)


cmake_minimum_required(VERSION 2.6)

message("Executing SERVER::CMakeLists.txt")

project(${SERVER} CXX)


if (TARGET ${PROJECT_NAME})
    message("Server is already defined")
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
    add_executable(${PROJECT_NAME} ${SERVER_SOURCES} ${SERVER_HEADERS})

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

    # linking witty for databse ORM
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_DBO})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_PG_SQL})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${WITTY_HTTP})

    configure_file(server.properties ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)

endif ()
