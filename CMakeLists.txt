cmake_minimum_required(VERSION 3.23)

set(CMAKE_C_STANDARD 23)

project(mylib VERSION 0.0.1
	DESCRIPTION "A game-making library for OpenGL and C using SDL2 intended for simple games")
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.c)
add_library(mylib SHARED ${SOURCES})
set_target_properties(mylib PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(mylib PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR})
set_target_properties(mylib PROPERTIES PUBLIC_HEADER include/mylib.h)
target_include_directories(mylib PRIVATE include)
target_include_directories(mylib PRIVATE src)

include(GNUInstallDirs)

install(TARGETS mylib
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(mylib.pc.in mylib.pc @ONLY)

install(FILES ${CMAKE_BINARY_DIR}/mylib.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)