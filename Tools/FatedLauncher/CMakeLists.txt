cmake_minimum_required(VERSION 3.8)
project(FatedSolution LANGUAGES CSharp)

# Add subprojects
add_subdirectory(FatedLauncher)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT FatedLauncher)

set(FATEDQUEST_LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../FatedQuest.Libraries.CSharp)
add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/StandardOperations StandardOperations)