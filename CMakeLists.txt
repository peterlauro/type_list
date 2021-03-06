﻿cmake_minimum_required (VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project ("type_list")

include(cmake/googletest.cmake)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -pedantic -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX")
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_compile_options(/permissive-)
endif()

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/debug)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/debug)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/debug)
else()
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/release)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/release)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/debug)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/debug)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_BINARY_DIR}/debug)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/release)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/release)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${CMAKE_CURRENT_BINARY_DIR}/release)

set(TARGET_NAME StdX)
set(TARGET_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

set(INTERFACE_SOURCES
    ${TARGET_INCLUDE_DIR}/type_list.h
    ${TARGET_INCLUDE_DIR}/type_traits.h
    ${TARGET_INCLUDE_DIR}/bits/at.h
    ${TARGET_INCLUDE_DIR}/bits/back.h
    ${TARGET_INCLUDE_DIR}/bits/contains.h
    ${TARGET_INCLUDE_DIR}/bits/findfirstnotof.h
    ${TARGET_INCLUDE_DIR}/bits/findfirstof.h
    ${TARGET_INCLUDE_DIR}/bits/findif.h
    ${TARGET_INCLUDE_DIR}/bits/findifnot.h
    ${TARGET_INCLUDE_DIR}/bits/findlastnotof.h
    ${TARGET_INCLUDE_DIR}/bits/findlastof.h
    ${TARGET_INCLUDE_DIR}/bits/findtemplate.h
    ${TARGET_INCLUDE_DIR}/bits/flatten.h
    ${TARGET_INCLUDE_DIR}/bits/foreach.h
    ${TARGET_INCLUDE_DIR}/bits/front.h
    ${TARGET_INCLUDE_DIR}/bits/get.h
    ${TARGET_INCLUDE_DIR}/bits/insert.h
    ${TARGET_INCLUDE_DIR}/bits/maxelement.h
    ${TARGET_INCLUDE_DIR}/bits/minelement.h
    ${TARGET_INCLUDE_DIR}/bits/popback.h
    ${TARGET_INCLUDE_DIR}/bits/popfront.h
    ${TARGET_INCLUDE_DIR}/bits/pushback.h
    ${TARGET_INCLUDE_DIR}/bits/pushfront.h
    ${TARGET_INCLUDE_DIR}/bits/remove.h
    ${TARGET_INCLUDE_DIR}/bits/removeif.h
    ${TARGET_INCLUDE_DIR}/bits/replace.h
    ${TARGET_INCLUDE_DIR}/bits/replaceif.h
    ${TARGET_INCLUDE_DIR}/bits/reverse.h
    ${TARGET_INCLUDE_DIR}/bits/second.h
    ${TARGET_INCLUDE_DIR}/bits/sort.h
    ${TARGET_INCLUDE_DIR}/bits/split.h
    ${TARGET_INCLUDE_DIR}/bits/transform.h
    ${TARGET_INCLUDE_DIR}/bits/unique.h
    )

add_library(${TARGET_NAME} INTERFACE)

target_sources(${TARGET_NAME} INTERFACE ${INTERFACE_SOURCES})

target_include_directories(${TARGET_NAME} INTERFACE ${TARGET_INCLUDE_DIR})

fetch_googletest(${PROJECT_SOURCE_DIR}/cmake ${PROJECT_BINARY_DIR}/googletest)
enable_testing()
add_subdirectory(test)
