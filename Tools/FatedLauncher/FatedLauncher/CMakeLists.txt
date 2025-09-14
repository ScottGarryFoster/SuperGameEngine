cmake_minimum_required(VERSION 3.8)

project(FatedLauncher LANGUAGES CSharp)

# Explicit glob for only .cs files (no CMake files, no extras)
file(GLOB_RECURSE CS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cs")

# Filter out files inside the binary/build directory
foreach(file ${CS_SOURCES})
    string(FIND "${file}" "${CMAKE_BINARY_DIR}" in_build_dir)
    if(NOT in_build_dir EQUAL -1)
        list(REMOVE_ITEM CS_SOURCES "${file}")
    endif()
endforeach()

# Define the executable
add_executable(FatedLauncher ${CS_SOURCES})

# Ensure Resources folder is copied to output
file(GLOB RESOURCE_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources/*"
)

foreach(res ${RESOURCE_FILES})
    add_custom_command(TARGET FatedLauncher POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${res}"
                "$<TARGET_FILE_DIR:FatedLauncher>"
    )
endforeach()

# Output directory
set_target_properties(FatedLauncher PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)

# .NET Framework references for WinForms app
set_property(TARGET FatedLauncher PROPERTY VS_DOTNET_REFERENCES
    "System"
    "System.Windows.Forms"
    "System.Drawing"
)

# Suppress console window
set_property(TARGET FatedLauncher PROPERTY VS_DOTNET_OUTPUT_TYPE "WinExe")

# Our Project References
#set(FATEDQUEST_LIBRARIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../FatedQuest.Libraries.CSharp)
#add_subdirectory(${FATEDQUEST_LIBRARIES_DIR}/StandardOperations StandardOperations)
#set_property(TARGET FatedLauncher APPEND PROPERTY VS_DOTNET_REFERENCES
#    "StandardOperations"
#)
#add_dependencies(FatedLauncher StandardOperations)

target_link_libraries(FatedLauncher PRIVATE StandardOperations)