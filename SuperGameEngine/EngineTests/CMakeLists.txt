cmake_minimum_required(VERSION 3.20)

project(SuperGameEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug")

# Define output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}/Debug")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}/Release")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_TOOLS_DEBUG "${CMAKE_BINARY_DIR}/Tools_Debug")

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

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

# Precompiled headers
set(PCH_HEADER pch.h)
set(PCH_SOURCE pch.cpp)

add_library(precompiled STATIC ${PCH_SOURCE})
if(MSVC)
    target_precompile_headers(precompiled PUBLIC ${PCH_HEADER})
endif()

# Add the executable
add_executable(SuperGameEngine ${SOURCE_FILES})
target_precompile_headers(SuperGameEngine REUSE_FROM precompiled)

# Compiler definitions based on build type
target_compile_definitions(SuperGameEngine PRIVATE
    $<$<CONFIG:Debug>:WIN32;_DEBUG;_CONSOLE>
    $<$<CONFIG:Tools_Debug>:WIN32;_DEBUG;_CONSOLE>
    $<$<CONFIG:Release>:WIN32;NDEBUG;_CONSOLE>
)

# Set compiler flags
if (MSVC)
    target_compile_options(SuperGameEngine PRIVATE
        /W3 /MD$<$<CONFIG:Debug>:d>
        $<$<CONFIG:Debug>:/Od>
        $<$<CONFIG:Release>:/O2 /Oi>
    )
    target_link_options(SuperGameEngine PRIVATE
        $<$<CONFIG:Debug>:/DEBUG>
        $<$<CONFIG:Release>:/OPT:REF /OPT:ICF>
    )
endif()

# Link libraries
add_subdirectory(../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../../FatedQuest.Libraries/SharedEnums SharedEnums)
add_subdirectory(../../FatedQuest.Libraries/StandardObjects StandardObjects)
add_subdirectory(../../FatedQuest.Libraries/StandardOperations StandardOperations)
add_subdirectory(../../FatedQuest.Libraries/StoredDocument StoredDocument)
add_subdirectory(../../FatedQuest.Libraries/XmlDocument XmlDocument)
add_subdirectory(../Engine Engine)

# Link dependencies
target_link_libraries(SuperGameEngine
    Logger
    Observer
    SharedEnums
    StandardObjects
    StandardOperations
    StoredDocument
    XmlDocument
    Engine
)

# Nuget Packages
FetchContent_Declare(
    RapidXML
    URL "https://www.nuget.org/api/v2/package/rapidxml/1.13"
    DOWNLOAD_NO_EXTRACT TRUE
)
FetchContent_MakeAvailable(RapidXML)

# Manually set RapidXML paths from NuGet
set(RapidXML_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/rapidxml-src/include")

# Testing
target_link_libraries(SuperGameEngine
    GTest::GTest
    GTest::Main
)

# Include GoogleTest and RapidXML
find_package(GTest REQUIRED)

# Enable testing
enable_testing()
add_test(NAME SuperGameEngineTests COMMAND SuperGameEngine)
