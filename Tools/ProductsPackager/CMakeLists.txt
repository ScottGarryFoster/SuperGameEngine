cmake_minimum_required(VERSION 3.20)
option(ENABLE_TESTS "Enable test projects in the solution" OFF)

if(ENABLE_TESTS)
    project(ProductsPackager-WithTests)
else()
    project(ProductsPackager)
endif()

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find and use vcpkg
if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/Build/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
message("CMAKE_TOOLCHAIN_FILE set to ${CMAKE_TOOLCHAIN_FILE}")
message("CMAKE_PREFIX_PATH set to ${CMAKE_PREFIX_PATH}")

# Define solution-wide configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# Add subdirectories in main
add_subdirectory(ProductsPackager)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ProductsPackager)

# Libraries under FatedQuest.Libraries
add_subdirectory(../../FatedQuest.Libraries/BinaryOperations BinaryOperations)
add_subdirectory(../../FatedQuest.Libraries/StandardOperations StandardOperations)
add_subdirectory(../../FatedQuest.Libraries/GamePackage GamePackage)
add_subdirectory(../../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../FatedQuest.Libraries/SharedEnums SharedEnums)

# Solution Folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(StandardOperations PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(GamePackage PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(BinaryOperations PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Logger PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Observer PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(SharedEnums PROPERTIES FOLDER "FatedQuest.Libraries")

if(ENABLE_TESTS)
    add_subdirectory(../../FatedQuest.Libraries/GamePackageTests GamePackageTests)
    add_subdirectory(../../FatedQuest.Libraries/StandardOperationsTests StandardOperationsTests)

    set_target_properties(GamePackageTests PROPERTIES FOLDER "FatedQuest.Libraries")
    set_target_properties(StandardOperationsTests PROPERTIES FOLDER "FatedQuest.Libraries")

    set_target_properties(gmock PROPERTIES FOLDER "External")
    set_target_properties(gmock_main PROPERTIES FOLDER "External")
    set_target_properties(gtest PROPERTIES FOLDER "External")
    set_target_properties(gtest_main PROPERTIES FOLDER "External")
endif()