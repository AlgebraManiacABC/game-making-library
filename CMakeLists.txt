cmake_minimum_required(VERSION 3.23)

project(llgml VERSION 0.2.0
	DESCRIPTION "A game-making library for OpenGL and C using SDL2 intended for simple games"
    LANGUAGES C)
set(PRERELEASE "alpha.7")

set(CMAKE_C_STANDARD 23)

# Low-Level Game-Making Library
file(GLOB SOURCES CONFIGURE_DEPENDS src/*.c)
add_library(llgml SHARED ${SOURCES})
set_target_properties(llgml PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR})
if(MSVC)
	# ensure an import lib is generated even without __declspec(dllexport)
	set_target_properties(llgml PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON
			ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
			LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib/$<CONFIG>"
			RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>")
endif()

# Library's Public vs Private Headers
set(PUBLIC_INC  "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(INTERNAL_INC "${CMAKE_CURRENT_SOURCE_DIR}/include/internal")
target_include_directories(llgml
		PUBLIC
		$<BUILD_INTERFACE:${PUBLIC_INC}>
		$<INSTALL_INTERFACE:include>        # only the public dir for consumers
		PRIVATE
		$<BUILD_INTERFACE:${INTERNAL_INC}>  # internal only while building this project
)

# Define for private headers to guard accidental inclusion by users
target_compile_definitions(llgml PRIVATE PROJECT_INTERNAL_BUILD)
# For improved safety
if(MSVC)
	target_compile_options(llgml PRIVATE /W4 /WX /wd4100 /wd4324)
else()
	target_compile_options(llgml PRIVATE -Wall -Werror -Wextra -Wpedantic -Wno-unused)
endif()

# Dependencies:
find_package(SDL2 REQUIRED)
find_package(GLEW CONFIG QUIET)
find_package(OpenGL REQUIRED)
find_library(M_LIB m)
find_package(cglm CONFIG QUIET)

# GLEW fallbacks etc.
if(NOT glew_FOUND)
	find_package(GLEW REQUIRED)  # Module finder
endif()

set(GLEW_LINK "")
if(TARGET GLEW::GLEW)
	set(GLEW_LINK GLEW::GLEW)
elseif(TARGET GLEW::glew_s)
	set(GLEW_LINK GLEW::glew_s)
	target_compile_definitions(llgml PRIVATE GLEW_STATIC)
	target_compile_definitions(llgml_test PRIVATE GLEW_STATIC)
elseif(DEFINED GLEW_LIBRARIES)
	set(GLEW_LINK ${GLEW_LIBRARIES})
	if(DEFINED GLEW_INCLUDE_DIRS)
		target_include_directories(llgml PRIVATE ${GLEW_INCLUDE_DIRS})
		target_include_directories(llgml_test PRIVATE ${GLEW_INCLUDE_DIRS})
	endif()
else()
	message(FATAL_ERROR "GLEW found, but no usable targets/vars exposed.")
endif()

# CGLM Fallback: fetch cglm from source if not found
if(NOT cglm_FOUND)
    include(FetchContent)
    set(CGLM_STATIC ON  CACHE BOOL "" FORCE)
    FetchContent_Declare(cglm
            GIT_REPOSITORY https://github.com/recp/cglm.git
            GIT_TAG v0.9.2
    )
    FetchContent_MakeAvailable(cglm)
endif()

# Normalize whatever cglm defined to the canonical name cglm::cglm
if(NOT TARGET cglm::cglm)
    if(TARGET cglm)                           # many versions define this
        add_library(cglm::cglm ALIAS cglm)
    elseif(TARGET cglm_shared)
        add_library(cglm::cglm ALIAS cglm_shared)
    elseif(TARGET cglm_static)
        add_library(cglm::cglm ALIAS cglm_static)
    elseif(TARGET cglm::cglm-header-only)     # if they provide an interface target
        add_library(cglm::cglm ALIAS cglm::cglm-header-only)
    elseif(TARGET cglm_headers)               # older/alt interface name, just in case
        add_library(cglm::cglm ALIAS cglm_headers)
    else()
        message(FATAL_ERROR "cglm fetched but no known target was defined")
    endif()
endif()

# Testing
enable_testing()
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS test/*.c)
add_executable(llgml_test ${TEST_SOURCES})
target_include_directories(llgml_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
if(MSVC)
	target_compile_options(llgml_test PRIVATE /W4 /WX /wd4100 /wd4324)
else()
	target_compile_options(llgml_test PRIVATE -Wall -Werror -Wextra -Wpedantic -Wno-unused)
endif()
add_test(NAME llgml_test COMMAND llgml_test)
if(WIN32)
	set_tests_properties(llgml_test PROPERTIES
			ENVIRONMENT "PATH=$<TARGET_FILE_DIR:llgml>;$ENV{PATH}")
endif()

# Link dependencies
if(M_LIB)
	target_link_libraries(llgml PRIVATE ${M_LIB})
	target_link_libraries(llgml_test PRIVATE ${M_LIB})
endif()

if (WIN32)
	target_link_libraries(llgml_test PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(llgml PRIVATE	SDL2::SDL2 ${GLEW_LINK} OpenGL::GL cglm::cglm)
target_link_libraries(llgml_test PRIVATE SDL2::SDL2 ${GLEW_LINK} OpenGL::GL cglm::cglm llgml)

# Install
include(GNUInstallDirs)

install(TARGETS llgml
        EXPORT llgmlTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Install all public headers (keep internals out)
install(DIRECTORY ${PUBLIC_INC}/
		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
		FILES_MATCHING
		PATTERN "*.h"
		PATTERN "internal*" EXCLUDE
)

# Export targets for find_package
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/llgmlConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)
configure_package_config_file(
        ${CMAKE_CURRENT_LIST_DIR}/cmake/llgmlConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/llgmlConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llgml)
install(EXPORT llgmlTargets
        NAMESPACE llgml::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llgml)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/llgmlConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/llgmlConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/llgml)

# pkg-config (UNIX)
if (UNIX)
	configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/llgml.pc.in
			${CMAKE_CURRENT_BINARY_DIR}/llgml.pc @ONLY)
	install(FILES ${CMAKE_CURRENT_BINARY_DIR}/llgml.pc
			DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/pkgconfig)
endif()

set(CPACK_PACKAGE_NAME "llgml")
set(CPACK_PACKAGE_VERSION "${PROJECT_VERSION}")
if(PRERELEASE)
	set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}-${PRERELEASE}")
endif()
set(CPACK_GENERATOR "TGZ;ZIP")
set(CPACK_PACKAGE_FILE_NAME "llgml-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")
include(CPack)
