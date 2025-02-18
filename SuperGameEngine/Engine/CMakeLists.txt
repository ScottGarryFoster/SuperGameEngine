cmake_minimum_required(VERSION 3.20)
project(Engine LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Available build types" FORCE)

# Collect source files
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")
file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE PCH_FILES "pch.cpp")

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
if(NOT TARGET Engine)
    add_library(Engine STATIC ${SOURCE_FILES} ${HEADER_FILES} ${PCH_FILES})
endif()

# Include directories
target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Enable precompiled headers
set(PCH_HEADER "pch.h")
set(PCH_SOURCE "src/pch.cpp")

if(MSVC)
    target_precompile_headers(Engine PRIVATE ${PCH_HEADER})
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(Engine PRIVATE _WINDOWS)
    target_compile_options(Engine PRIVATE /W3 /permissive- /Zc:preprocessor /MP)
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release Tools_Debug)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(Engine PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "Engine_${OUTPUTCONFIG}"
    )
endforeach()

# Use NuGet to fetch SDL2 and RapidXML
include(FetchContent)

FetchContent_Declare(
    SDL2
    URL "https://www.nuget.org/api/v2/package/sdl2.nuget/2.30.9"
    DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_Declare(
    RapidXML
    URL "https://www.nuget.org/api/v2/package/rapidxml/1.13"
    DOWNLOAD_NO_EXTRACT TRUE
)

FetchContent_MakeAvailable(SDL2 RapidXML)

# Manually set SDL2 paths from NuGet
set(SDL2_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/sdl2-src/include")
set(SDL2_LIBRARY "${CMAKE_BINARY_DIR}/_deps/sdl2-src/lib/x64/SDL2.lib")

# Manually set RapidXML paths from NuGet
set(RapidXML_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/rapidxml-src/include")

# Include and link dependencies
target_include_directories(Engine PRIVATE ${SDL2_INCLUDE_DIR} ${RapidXML_INCLUDE_DIR})
target_link_libraries(Engine ${SDL2_LIBRARY})