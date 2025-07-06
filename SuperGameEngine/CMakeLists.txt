cmake_minimum_required(VERSION 3.20)
option(ENABLE_TESTS "Enable tests" OFF)
option(ENABLE_TOOLS "Enable tools" OFF)

message(STATUS "ENABLE_TESTS: ${ENABLE_TESTS}")
message(STATUS "ENABLE_TOOLS: ${ENABLE_TOOLS}")
message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CONFIGURATION_TYPES: ${CMAKE_CONFIGURATION_TYPES}")
set(CMAKE_BUILD_TYPE Debug)

# Name the project such that each solution could have its own name
if(ENABLE_TOOLS)
    if(ENABLE_TESTS)
        project(SuperGameEngine-Tools-WithTests)
    else()
        project(SuperGameEngine-Tools)
    endif()
else()
    if(ENABLE_TESTS)
        project(SuperGameEngine-WithTests)
    else()
        project(SuperGameEngine)
    endif()
endif()


# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and use vcpkg
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/Build/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
message("CMAKE_TOOLCHAIN_FILE set to ${CMAKE_TOOLCHAIN_FILE}")
message("CMAKE_PREFIX_PATH set to ${CMAKE_PREFIX_PATH}")

# Define solution-wide configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release;Tools_Debug" CACHE STRING "Configurations" FORCE)

# Add subdirectories
add_subdirectory(SuperGameEngine)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SuperGameEngine)
add_subdirectory(Engine)
add_subdirectory(Input)
if(ENABLE_TOOLS)
    add_subdirectory(Tools)
endif()


# Libraries under FatedQuest.Libraries
set(FATEDQUEST_LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../FatedQuest.Libraries)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/StandardObjects StandardObjects)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/StandardOperations StandardOperations)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/GamePackage GamePackage)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/BinaryOperations BinaryOperations)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/XmlDocument XmlDocument)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/Logger Logger)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/Observer Observer)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/ClassTypes ClassTypes)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/StoredDocument StoredDocument)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/SharedEnums SharedEnums)

# Solution Folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(StandardObjects PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StandardOperations PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(GamePackage PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(BinaryOperations PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(XmlDocument PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Logger PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Observer PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(ClassTypes PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StoredDocument PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(SharedEnums PROPERTIES FOLDER "FatedQuest.Libraries")

if(ENABLE_TESTS)
    add_subdirectory(EngineTests)
    add_subdirectory(InputTests)
    if(ENABLE_TOOLS)
        add_subdirectory(ToolsTests)
    endif()

    add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/StandardOperationsTests StandardOperationsTests)
    add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/XmlDocumentTests XmlDocumentTests)
    add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/StandardObjectsTests StandardObjectsTests)
    add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/GamePackageTests GamePackageTests)

    set_target_properties(XmlDocumentTests PROPERTIES FOLDER "FatedQuest.Libraries")
    set_target_properties(StandardOperationsTests PROPERTIES FOLDER "FatedQuest.Libraries")
    set_target_properties(StandardObjectsTests PROPERTIES FOLDER "FatedQuest.Libraries")
    set_target_properties(GamePackageTests PROPERTIES FOLDER "FatedQuest.Libraries")

    set_target_properties(gmock PROPERTIES FOLDER "External")
    set_target_properties(gmock_main PROPERTIES FOLDER "External")
    set_target_properties(gtest PROPERTIES FOLDER "External")
    set_target_properties(gtest_main PROPERTIES FOLDER "External")
endif()