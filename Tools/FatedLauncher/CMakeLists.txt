cmake_minimum_required(VERSION 3.20)
project(FatedLauncher)

# Define solution-wide configurations
set(CMAKE_CONFIGURATION_TYPES "Debug;Release")

# Add the subdirectory that contains the actual project
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
add_subdirectory(FatedLauncher)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT FatedLauncher)