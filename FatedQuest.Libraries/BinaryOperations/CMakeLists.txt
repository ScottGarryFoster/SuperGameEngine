cmake_minimum_required(VERSION 3.20)
project(BinaryOperations)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Available build types" FORCE)

# Collect source files
file(GLOB_RECURSE SOURCE_FILES "*.cpp" "*.h")
file(GLOB_RECURSE HEADER_FILES "*.h")
file(GLOB_RECURSE PCH_FILES "pch.cpp")

# Remove files from the "build" directory
list(FILTER SOURCE_FILES EXCLUDE REGEX "^build/")
list(FILTER HEADER_FILES EXCLUDE REGEX "^build/")

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
set(PCH_SOURCE "src/pch.cpp")

if(MSVC)
    target_precompile_headers(BinaryOperations PRIVATE ${PCH_HEADER})
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(BinaryOperations PRIVATE _WINDOWS)
    target_compile_options(BinaryOperations PRIVATE /W3 /permissive- /Zc:preprocessor /MP)
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release Tools_Debug)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(BinaryOperations PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "BinaryOperations_${OUTPUTCONFIG}"
    )
endforeach()

# Link libraries
add_subdirectory(../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../FatedQuest.Libraries/StandardOperations StandardOperations)

# Link dependencies
target_link_libraries(BinaryOperations
    Logger
    StandardOperations
)

# Use NuGet to fetch SDL2 and RapidXML
include(FetchContent)

FetchContent_Declare(
    Zlib
    URL "https://www.nuget.org/api/v2/package/zlib_static/1.2.11.12"
    DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_MakeAvailable(Zlib)

# Manually set paths from NuGet
set(NUGET_PACKAGES_DIR "${CMAKE_BINARY_DIR}/packages")

# Zlib
set(NUGET_ZLIB_DIR "${NUGET_PACKAGES_DIR}/zlib_static.1.2.11.12/build/native")
if (NOT EXISTS "${NUGET_ZLIB_DIR}")
    execute_process(
        COMMAND nuget install zlib_static -Version 1.2.11.12 -OutputDirectory ${NUGET_PACKAGES_DIR}
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )
endif()
set(ZLIB_INCLUDE_DIR "${NUGET_ZLIB_DIR}/include")
set(ZLIB_LIBRARY "${NUGET_ZLIB_DIR}/lib/zlibstatic.lib")

# Include and link dependencies
target_include_directories(BinaryOperations PRIVATE ${ZLIB_INCLUDE_DIR})
# target_link_libraries(BinaryOperations ${ZLIB_LIBRARY})
target_link_libraries(BinaryOperations Zlib)