cmake_minimum_required(VERSION 3.20)
project(SuperEnumGenerator)
include(../../../../FatedQuest.Libraries/CMake/Main.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Available build types" FORCE)

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
if(NOT TARGET SuperEnumGenerator)
    add_library(SuperEnumGenerator STATIC ${SOURCE_FILES} ${HEADER_FILES} ${PCH_FILES})
endif()

# Include directories
target_include_directories(SuperEnumGenerator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Enable precompiled headers
set(PCH_HEADER "pch.h")

if(MSVC)
    target_precompile_headers(SuperEnumGenerator PRIVATE ${PCH_HEADER})
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(SuperEnumGenerator PRIVATE _WINDOWS)
    target_compile_options(SuperEnumGenerator PRIVATE /W3 /permissive- /Zc:preprocessor /MP)
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release Tools_Debug)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(SuperEnumGenerator PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "SuperEnumGenerator${OUTPUTCONFIG}"
    )
endforeach()

# Get Packages
NugetInclude("rapidxml" SuperEnumGenerator)

# Link libraries
add_subdirectory(../../../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../../../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../../../../FatedQuest.Libraries/StandardObjects StandardObjects)
add_subdirectory(../../../../FatedQuest.Libraries/StandardOperations StandardOperations)
add_subdirectory(../../../../FatedQuest.Libraries/StoredDocument StoredDocument)
add_subdirectory(../../../../FatedQuest.Libraries/XmlDocument XmlDocument)

# Link dependencies
target_link_libraries(SuperEnumGenerator
    Logger
    Observer
    StandardObjects
    StandardOperations
    StoredDocument
    XmlDocument
)