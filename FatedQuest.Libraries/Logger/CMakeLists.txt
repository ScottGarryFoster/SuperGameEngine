cmake_minimum_required(VERSION 3.20)
option(ENABLE_TOOLS "Enable tools" OFF)
project(Logger)
include(../CMake/Main.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
if(ENABLE_TOOLS)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Available build types" FORCE)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<OR:$<CONFIG:Debug>,$<CONFIG:Tools_Debug>>:Debug>DLL")
else()
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available build types" FORCE)
endif()

# Collect source files
file(GLOB_RECURSE UNFILTERED_SOURCE_FILES "*.cpp")
file(GLOB_RECURSE UNFILTERED_HEADER_FILES "*.h")
file(GLOB_RECURSE PCH_FILES "pch.cpp")

# Filter out build directory
FilterDirectoryFromGiven(UNFILTERED_SOURCE_FILES "build" SOURCE_FILES)
FilterDirectoryFromGiven(UNFILTERED_HEADER_FILES "build" HEADER_FILES)

# Organizing filters based on actual structure with top-level grouping
foreach(FILE ${SOURCE_FILES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    file(RELATIVE_PATH GROUP_NAME "${CMAKE_CURRENT_SOURCE_DIR}" "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP_NAME "${GROUP_NAME}")
    source_group("Source Files\\${GROUP_NAME}" FILES "${FILE}")
endforeach()

foreach(FILE ${HEADER_FILES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    file(RELATIVE_PATH GROUP_NAME "${CMAKE_CURRENT_SOURCE_DIR}" "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP_NAME "${GROUP_NAME}")
    source_group("Header Files\\${GROUP_NAME}" FILES "${FILE}")
endforeach()

# Create the library
if(NOT TARGET Logger)
    add_library(Logger STATIC ${SOURCE_FILES} ${HEADER_FILES} ${PCH_FILES})
endif()

# Include directories
target_include_directories(Logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Enable precompiled headers
set(PCH_HEADER "pch.h")

if(MSVC)
    target_precompile_headers(Logger PRIVATE ${PCH_HEADER})
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(Logger PRIVATE _WINDOWS)
    target_compile_options(Logger PRIVATE /W3 /permissive- /Zc:preprocessor /MP)
endif()

# Include these by default in all CPP files.
if (MSVC)
    target_compile_options(Logger PRIVATE "/FI${PCH_HEADER}")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(Logger PRIVATE "-include ${PCH_HEADER}")
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release Tools_Debug)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(Logger PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "Logger_${OUTPUTCONFIG}"
    )
endforeach()

# Link libraries
add_subdirectory(../Observer Observer)

# Link dependencies
target_link_libraries(Logger PUBLIC
    Observer
)