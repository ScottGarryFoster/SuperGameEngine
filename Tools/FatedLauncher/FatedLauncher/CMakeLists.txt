cmake_minimum_required(VERSION 3.20)
include(../../../FatedQuest.Libraries/CMake/Main.cmake)

project(FatedLauncher CSharp)

# Collect source files
file(GLOB_RECURSE UNFILTERED_SOURCE_FILES "*.cs")

# Organizing filters based on actual structure with top-level grouping
foreach(FILE ${UNFILTERED_SOURCE_FILES})
    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
    file(RELATIVE_PATH GROUP_NAME "${CMAKE_CURRENT_SOURCE_DIR}" "${PARENT_DIR}")
    string(REPLACE "/" "\\" GROUP_NAME "${GROUP_NAME}")
    source_group("${GROUP_NAME}" FILES "${FILE}")
endforeach()

# Create executable
add_executable(${PROJECT_NAME} ${UNFILTERED_SOURCE_FILES})

set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_TARGET_FRAMEWORK_VERSION "v4.8")
set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DOTNET_REFERENCES
    "System"
    "System.Windows.Forms"
    "System.Drawing"
)

# Optional: Set output directory
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)