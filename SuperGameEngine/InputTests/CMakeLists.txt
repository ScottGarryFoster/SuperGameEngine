cmake_minimum_required(VERSION 3.20)
option(ENABLE_TOOLS "Enable tools" OFF)
project(InputTests)
include(../../FatedQuest.Libraries/CMake/Main.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
if(ENABLE_TOOLS)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Available build types" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_TOOLS_DEBUG "")
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

# Create executable
add_executable(InputTests  ${SOURCE_FILES} ${HEADER_FILES})
set_target_properties(InputTests PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")

# Set compiler options
if(MSVC)
    target_compile_definitions(InputTests PRIVATE _CRT_SECURE_NO_WARNINGS)
    target_compile_options(InputTests PRIVATE /W3)
endif()

# Include directories
target_include_directories(InputTests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Enable precompiled headers
set(PCH_HEADER "pch.h")

if(MSVC)
    target_precompile_headers(InputTests PRIVATE ${PCH_HEADER})
endif()

# Include these by default in all CPP files.
if (MSVC)
    target_compile_options(InputTests PRIVATE "/FI${PCH_HEADER}")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU")
    target_compile_options(InputTests PRIVATE "-include ${PCH_HEADER}")
endif()

# Platform-specific settings
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _CONSOLE)
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(InputTests PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "InputTests_${OUTPUTCONFIG}"
    )
endforeach()

# Get packages (must occur before projects below)
NugetInclude("rapidxml" InputTests)
NugetInclude("gtest" InputTests)
set_target_properties(InputTests PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD_RELEASE ON)

# Link libraries
add_subdirectory(../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../../FatedQuest.Libraries/StoredDocument StoredDocument)
add_subdirectory(../../FatedQuest.Libraries/XmlDocument XmlDocument)
add_subdirectory(../Engine Engine)
add_subdirectory(../Input Input)

# Link dependencies
target_link_libraries(InputTests PRIVATE
    Logger
    Observer
    StoredDocument
    XmlDocument
    Engine
    Input
    $<$<NOT:$<CONFIG:Release>>:GTest::gtest>
    $<$<NOT:$<CONFIG:Release>>:GTest::gtest_main>
)