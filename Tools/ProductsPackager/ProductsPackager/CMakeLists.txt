cmake_minimum_required(VERSION 3.20)
project(ProductsPackager)
include(../../../FatedQuest.Libraries/CMake/Main.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Available build types" FORCE)
set(CMAKE_EXE_LINKER_FLAGS_TOOLS_DEBUG "")

# Collect source files
file(GLOB_RECURSE UNFILTERED_SOURCE_FILES "*.cpp" "*.h")
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

# Create executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

# Include directories
target_include_directories(ProductsPackager PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Enable precompiled headers
set(PCH_HEADER "pch.h")
set(PCH_SOURCE "src/pch.cpp")

if(MSVC)
    target_precompile_headers(ProductsPackager PRIVATE ${PCH_HEADER})
endif()

# Include these by default in all CPP files.
if (MSVC)
    target_compile_options(ProductsPackager PRIVATE "/FIcmake_pch.hxx" "/FIpch.h")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(ProductsPackager PRIVATE "-include cmake_pch.hxx;pch.h")
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CONSOLE)
endif()

# Set compiler options
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W3 /permissive- /Zc:preprocessor /MP)
    target_compile_definitions(${PROJECT_NAME} PRIVATE "UNICODE" "_UNICODE")
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(ProductsPackager PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "ProductsPackager_${OUTPUTCONFIG}"
    )
endforeach()

# Get Packages
NugetInclude("zlib" ProductsPackager)

# Link libraries
add_subdirectory(../../../FatedQuest.Libraries/BinaryOperations BinaryOperations)
add_subdirectory(../../../FatedQuest.Libraries/GamePackage GamePackage)
add_subdirectory(../../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../../../FatedQuest.Libraries/SharedEnums SharedEnums)
add_subdirectory(../../../FatedQuest.Libraries/StandardOperations StandardOperations)

# Link dependencies
target_link_libraries(ProductsPackager PUBLIC
    BinaryOperations
    GamePackage
    Logger
    Observer
    SharedEnums
    StandardOperations
)
