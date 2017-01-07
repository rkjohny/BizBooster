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

project(${WEB_APP} CXX)


if (TARGET ${PROJECT_NAME})
    message("App is already defined")
else ()
    message("Biulding app...")

    # stting the heared and source files path required by libcommon target
    set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

    # including heared files
    include_directories(${PROJECT_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    # including libjson include directory
    include_directories(${LIB_JSON_INCLUDE_DIR})

    #including libfio include directory
    include_directories(${LIB_FIO_INCLUDE_DIR})

    #including liblcrypto include directory
    include_directories(${LIB_LCRYPTO_INCLUDE_DIR})

    #including libdbo include directory
    include_directories(${LIB_DBO_INCLUDE_DIR})


    file(GLOB APP_HEADERS ${PROJECT_INCLUDE_DIR}/*.h)
    file(GLOB APP_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)


    

    #creating target server
    add_executable(${PROJECT_NAME} ${APP_SOURCES} ${APP_HEADERS})

    # linking libjson library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_DBO})

    # linking libjson library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_JSON})

    # linking liblcrypto library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_LCRYPTO})

    # linking libjson library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_FIO})

    # linking libcommon library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_COMMON})

    # linking third party library dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CPP_REST})

    # linking witty for databse ORM
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_HTTP})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_DBO})
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_WITTY_PG_SQL})
    
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_BOOST})

#    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_SSL})
#    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CRYPTO})

    target_link_libraries(${PROJECT_NAME} PUBLIC /usr/lib/x86_64-linux-gnu/libssl.a)
    target_link_libraries(${PROJECT_NAME} PUBLIC /usr/lib/x86_64-linux-gnu/libcrypto.a)

    target_link_libraries(${PROJECT_NAME} PUBLIC z)
    target_link_libraries(${PROJECT_NAME} PUBLIC dl)

    configure_file(app.properties ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)
    configure_file(wt_config.xml ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)


    #TODO: copies only first time
    #file(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/resources)
    file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${EXECUTABLE_OUTPUT_PATH}/)

    #install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/resources/ DESTINATION ${EXECUTABLE_OUTPUT_PATH}/resources/ FILES_MATCHING PATTERN "*.*")

    #add_custom_command(TARGET MyTarget PRE_BUILD
    #                   COMMAND ${CMAKE_COMMAND} -E copy_directory
    #                       ${CMAKE_CURRENT_SOURCE_DIR}/releases $<TARGET_FILE_DIR:MyTarget>)

endif ()
