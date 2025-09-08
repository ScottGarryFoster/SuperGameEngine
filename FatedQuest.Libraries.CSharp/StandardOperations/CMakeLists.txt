cmake_minimum_required(VERSION 3.8)

project(StandardOperations LANGUAGES CSharp)

file(GLOB_RECURSE CS_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cs")

# Filter out files inside the binary/build directory
foreach(file ${CS_SOURCES})
    string(FIND "${file}" "${CMAKE_BINARY_DIR}" in_build_dir)
    if(NOT in_build_dir EQUAL -1)
        list(REMOVE_ITEM CS_SOURCES "${file}")
    endif()
endforeach()
add_library(StandardOperations ${CS_SOURCES})
set_property(TARGET StandardOperations PROPERTY FOLDER "FatedQuest.Libraries")

# Resource Directory.
file(GLOB RESOURCE_FILES
    "${CMAKE_SOURCE_DIR}/Resources/*"
)
foreach(res ${RESOURCE_FILES})
    add_custom_command(TARGET StandardOperations POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${res}"
                "$<TARGET_FILE_DIR:StandardOperations>"
    )
endforeach()

# Output directory
set_target_properties(StandardOperations PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/$<CONFIG>"
)


set_property(TARGET StandardOperations PROPERTY VS_DOTNET_REFERENCES
    "System"
)

# Make a library not an exe.
set_property(TARGET StandardOperations PROPERTY VS_DOTNET_OUTPUT_TYPE "Library")