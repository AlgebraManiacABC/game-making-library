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

add_test(NAME test COMMAND test)
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS test/*.c)
add_executable(test ${TEST_SOURCES})
target_include_directories(test PRIVATE include)
target_link_libraries(test llgml)
target_link_libraries(test m)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

find_package(GLEW REQUIRED GLEW_USE_STATIC_LIBS)
include_directories(${GLEW_INCLUDE_DIRS})
if(UNIX)
	target_link_libraries(${PROJECT_NAME} "/usr/lib/x86_64-linux-gnu/libGLEW.so")
else()
	target_link_libraries(${PROJECT_NAME} "C:/Program Files (x86)/glew/lib/libglew32.dll.a")
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

if(UNIX)
    include(GNUInstallDirs)

    install(TARGETS llgml
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    configure_file(llgml.pc.in llgml.pc @ONLY)

    install(FILES ${CMAKE_BINARY_DIR}/llgml.pc DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
endif()