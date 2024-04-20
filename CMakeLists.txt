cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_STANDARD 23)

project(llgml VERSION 0.0.1
	DESCRIPTION "A game-making library for OpenGL and C using SDL2 intended for simple games")
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.c)
add_library(llgml SHARED ${SOURCES})
set_target_properties(llgml PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(llgml PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(llgml PROPERTIES PUBLIC_HEADER include/llgml.h)
target_include_directories(llgml PRIVATE include)
target_include_directories(llgml PRIVATE src)

add_test(NAME llgml-test COMMAND llgml-test)
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS test/*.c)
add_executable(llgml-test ${TEST_SOURCES})
target_include_directories(llgml-test PRIVATE include)
target_link_libraries(llgml-test llgml)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

if(UNIX)
    include(GNUInstallDirs)

    install(TARGETS llgml
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    configure_file(llgml.pc.in llgml.pc @ONLY)

    install(FILES ${CMAKE_BINARY_DIR}/llgml.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
endif()