cmake_minimum_required(VERSION 3.20)
option(ENABLE_TOOLS "Enable tools" OFF)
project(BinaryOperations)
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
file(GLOB_RECURSE UNFILTERED_SOURCE_FILES "BinaryZip/*.cpp")
file(GLOB_RECURSE UNFILTERED_HEADER_FILES "BinaryZip/*.h")
file(GLOB_RECURSE PCH_FILES "pch.cpp")

# If generated files (from FetchContent) are causing issues, exclude them
set_source_files_properties(${SOURCE_FILES} PROPERTIES HEADER_FILE_ONLY OFF)
set_source_files_properties(${HEADER_FILES} PROPERTIES HEADER_FILE_ONLY OFF)

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
if(NOT TARGET BinaryOperations)
    add_library(BinaryOperations STATIC ${SOURCE_FILES} ${HEADER_FILES} ${PCH_FILES})
endif()

# Include directories
target_include_directories(BinaryOperations PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Enable precompiled headers
set(PCH_HEADER "pch.h")

if(MSVC)
    target_precompile_headers(BinaryOperations PRIVATE ${PCH_HEADER})
endif()

# Include these by default in all CPP files.
if (MSVC)
    target_compile_options(BinaryOperations PRIVATE "/FI${PCH_HEADER}")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(BinaryOperations PRIVATE "-include ${PCH_HEADER}")
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(BinaryOperations PRIVATE _WINDOWS)
    target_compile_options(BinaryOperations PRIVATE
      /W3
      /permissive-
      /Zc:preprocessor
      /MP
      
      # Ensure Tools Debug and Debug have symbols.
      $<$<OR:$<CONFIG:Debug>,$<CONFIG:Tools_Debug>>:/Zi>
      $<$<OR:$<CONFIG:Debug>,$<CONFIG:Tools_Debug>>:/Od>
    )
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release Tools_Debug)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(BinaryOperations PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "BinaryOperations_${OUTPUTCONFIG}"
    )
endforeach()

# Link libraries
add_subdirectory(../Logger Logger)
add_subdirectory(../StandardOperations StandardOperations)

# Link dependencies
target_link_libraries(BinaryOperations PRIVATE
    Logger
    StandardOperations
)

# Get Packages
NugetInclude("zlib" BinaryOperations)