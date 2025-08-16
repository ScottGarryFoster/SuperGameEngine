cmake_minimum_required(VERSION 3.20)
option(ENABLE_TOOLS "Enable tools" OFF)
message(STATUS "Project(SuperGameEngine): ENABLE_TOOLS: ${ENABLE_TOOLS}")

project(SuperGameEngine)
include(../../FatedQuest.Libraries/CMake/Main.cmake)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define build configurations
if(ENABLE_TOOLS)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Available build types" FORCE)
    set(CMAKE_EXE_LINKER_FLAGS_TOOLS_DEBUG "")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<OR:$<CONFIG:Debug>,$<CONFIG:Tools_Debug>>:Debug>DLL")
    
    set(CMAKE_C_FLAGS_Tools_Debug "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING "C flags for Tools_Debug" FORCE)
    set(CMAKE_CXX_FLAGS_Tools_Debug "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING "C++ flags for Tools_Debug" FORCE)
else()
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Available build types" FORCE)
endif()


# Detect platform
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(TARGET_ARCH "x64")
else()
    set(TARGET_ARCH "Win32")
endif()

# Collect source files
file(GLOB_RECURSE UNFILTERED_SOURCE_FILES "*.cpp")
file(GLOB_RECURSE UNFILTERED_HEADER_FILES "*.h")

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
target_include_directories(SuperGameEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Platform-specific settings
if(WIN32)
    target_compile_definitions(SuperGameEngine PRIVATE _WINDOWS)
    target_compile_options(SuperGameEngine PRIVATE
      /W3
      /permissive-
      /Zc:preprocessor
      /MP
      
      # Ensure Tools Debug and Debug have symbols.
      $<$<OR:$<CONFIG:Debug>,$<CONFIG:Tools_Debug>>:/Zi>
      $<$<OR:$<CONFIG:Debug>,$<CONFIG:Tools_Debug>>:/Od>
    )

    # then tell the linker to emit debug info in those configs
    target_link_options(SuperGameEngine PRIVATE
      $<$<OR:$<CONFIG:Debug>,$<CONFIG:Tools_Debug>>:/DEBUG>
    )
endif()

# Set configurations
foreach(OUTPUTCONFIG Debug Release Tools_Debug)
    string(TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG_UPPER)
    set_target_properties(SuperGameEngine PROPERTIES 
        OUTPUT_NAME_${OUTPUTCONFIG_UPPER} "SuperGameEngine_${OUTPUTCONFIG}"
    )
endforeach()

# Get Packages
NugetInclude("rapidxml" SuperGameEngine)
NugetInclude("zlib" SuperGameEngine)
NugetInclude("sdl2" SuperGameEngine)
NugetInclude("sdl2Image" SuperGameEngine)
NugetInclude("sdl2Mixer" SuperGameEngine)

# Link libraries
add_subdirectory(../Engine Engine)
add_subdirectory(../Input Input)
add_subdirectory(../../FatedQuest.Libraries/BinaryOperations BinaryOperations)
add_subdirectory(../../FatedQuest.Libraries/ClassTypes ClassTypes)
add_subdirectory(../../FatedQuest.Libraries/GamePackage GamePackage)
add_subdirectory(../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../../FatedQuest.Libraries/SharedEnums SharedEnums)
add_subdirectory(../../FatedQuest.Libraries/StandardObjects StandardObjects)
add_subdirectory(../../FatedQuest.Libraries/StandardOperations StandardOperations)
add_subdirectory(../../FatedQuest.Libraries/StoredDocument StoredDocument)
add_subdirectory(../../FatedQuest.Libraries/XmlDocument XmlDocument)
add_subdirectory(../../FatedQuest.Libraries/Exceptions Exceptions)

# Link dependencies
target_link_libraries(SuperGameEngine PUBLIC
    Engine
    Input
    BinaryOperations
    ClassTypes
    GamePackage
    Logger
    Observer
    SharedEnums
    StandardObjects
    StandardOperations
    StoredDocument
    XmlDocument
    Exceptions
)

# Tools only dependencies
if(ENABLE_TOOLS)
    message(STATUS "SuperGameEngine: Linking Tools Dependancies")
    add_subdirectory(../Tools Tools)
    target_link_libraries(SuperGameEngine PUBLIC Tools)
endif()

# Set preprocessor definitions per configuration
if(ENABLE_TOOLS)
    target_compile_definitions(SuperGameEngine PRIVATE
        $<$<CONFIG:Debug>:DEBUG _DEBUG _CONSOLE>
        $<$<CONFIG:Release>:NDEBUG>
        $<$<CONFIG:Tools_Debug>:_TOOLS _DEBUG _CONSOLE>
    )
else()
    target_compile_definitions(SuperGameEngine PRIVATE
        $<$<CONFIG:Debug>:DEBUG _DEBUG _CONSOLE>
        $<$<CONFIG:Release>:NDEBUG>
    )
endif()

# Set the executable's subsystem
set_target_properties(SuperGameEngine PROPERTIES LINK_FLAGS_DEBUG "/SUBSYSTEM:CONSOLE")
set_target_properties(SuperGameEngine PROPERTIES LINK_FLAGS_TOOLS_DEBUG "/SUBSYSTEM:CONSOLE")