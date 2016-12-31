cmake_minimum_required(VERSION 2.6)

message("Executing SERVICE::CMakeLists.txt")

project(${SERVICE} CXX)


if (TARGET ${PROJECT_NAME})
    message("Rest service is already defined")
else ()
    message("Biulding rest service...")

    # stting the heared and source files path required by libcommon target
    set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
    set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

    # including heared files
    include_directories(${PROJECT_INCLUDE_DIR})

    # including libcommon include directory
    include_directories(${LIB_COMMON_INCLUDE_DIR})

    # including libjson include directory
    include_directories(${LIB_JSON_INCLUDE_DIR})

    # including libjson include directory
    include_directories(${LIB_DBO_INCLUDE_DIR})

    # including libapi include directory
    include_directories(${LIB_API_INCLUDE_DIR})

    #including libfio include directory
    include_directories(${LIB_FIO_INCLUDE_DIR})

    #including liblcrypto include directory
    include_directories(${LIB_LCRYPTO_INCLUDE_DIR})

    file(GLOB SERVICE_HEADERS ${PROJECT_INCLUDE_DIR}/*.h)
    file(GLOB SERVICE_SOURCES ${PROJECT_SOURCE_DIR}/*.cpp)

    #creating target service
    add_executable(${PROJECT_NAME} ${SERVICE_SOURCES} ${SERVICE_HEADERS})

    # linking libapi library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_API})
    
    # linking libjson library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_JSON})

    # linking libjson library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_DBO})

    # linking liblcrypto library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_LCRYPTO})

    # linking libfio library as dependences 
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_FIO})

    # linking libcommon library as dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_COMMON})


    # linking third party library dependencies
    target_link_libraries(${PROJECT_NAME} PUBLIC ${LIB_CPP_REST})

    # linking witty for databse ORM
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

target_link_libraries(${PROJECT_NAME} PUBLIC pthread)

    configure_file(service.properties ${EXECUTABLE_OUTPUT_PATH}/ COPYONLY UNIX)

endif ()
