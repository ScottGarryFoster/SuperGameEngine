option(ENABLE_TESTS "Enable test projects in the solution" OFF)

cmake_minimum_required(VERSION 3.20)
project(SuperGenerator)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define solution-wide configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# Add subdirectories in main
add_subdirectory(SuperGenerator)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SuperGenerator)
add_subdirectory(SuperEnumGenerator)

# Libraries under FatedQuest.Libraries
add_subdirectory(../../../FatedQuest.Libraries/StandardObjects StandardObjects)
add_subdirectory(../../../FatedQuest.Libraries/StandardOperations StandardOperations)
add_subdirectory(../../../FatedQuest.Libraries/XmlDocument XmlDocument)
add_subdirectory(../../../FatedQuest.Libraries/StoredDocument StoredDocument)
add_subdirectory(../../../FatedQuest.Libraries/Observer Observer)
add_subdirectory(../../../FatedQuest.Libraries/Logger Logger)
add_subdirectory(../../../FatedQuest.Libraries/SharedEnums SharedEnums)

# Solution Folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_target_properties(StandardObjects PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StandardOperations PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(XmlDocument PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(StoredDocument PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Observer PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(Logger PROPERTIES FOLDER "FatedQuest.Libraries")
set_target_properties(SharedEnums PROPERTIES FOLDER "FatedQuest.Libraries")

if(ENABLE_TESTS)
    add_subdirectory(../../../FatedQuest.Libraries/XmlDocumentTests XmlDocumentTests)

    set_target_properties(XmlDocumentTests PROPERTIES FOLDER "FatedQuest.Libraries")
    set_target_properties(gmock PROPERTIES FOLDER "External")
    set_target_properties(gmock_main PROPERTIES FOLDER "External")
    set_target_properties(gtest PROPERTIES FOLDER "External")
    set_target_properties(gtest_main PROPERTIES FOLDER "External")
endif()