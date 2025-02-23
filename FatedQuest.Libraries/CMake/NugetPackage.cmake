include(FetchContent)

# Function to filter out files in the directory
function(NugetInclude LIBRARY TARGET)
    if(${LIBRARY} STREQUAL "zlib")
        NugetIncludeZlib(${TARGET})
    endif()
    if(${LIBRARY} STREQUAL "rapidxml")
        NugetIncludeRapid(${TARGET})
    endif()
    if(${LIBRARY} STREQUAL "gtest")
        NugetIncludeGTest(${TARGET})
    endif()

endfunction()

function(NugetIncludeZlib TARGET)

    FetchContent_Declare(
        Zlib
        URL "https://www.nuget.org/api/v2/package/zlib_static/1.2.11.12"
        DOWNLOAD_NO_EXTRACT TRUE
    )
    FetchContent_MakeAvailable(Zlib)

    # Manually set RapidXML paths from NuGet
    set(NUGET_PACKAGES_DIR "${CMAKE_BINARY_DIR}/packages")

    # Zlib
    set(NUGET_ZLIB_DIR "${NUGET_PACKAGES_DIR}/zlib_static.1.2.11.12/build/native")
    if (NOT EXISTS "${NUGET_ZLIB_DIR}")
        execute_process(
            COMMAND nuget install zlib_static -Version 1.2.11.12 -OutputDirectory ${NUGET_PACKAGES_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()

    set(ZLIB_INCLUDE_DIR "${NUGET_ZLIB_DIR}/include")

    # Include and link dependencies
    message(STATUS "Linking ${TARGET} to ${ZLIB_INCLUDE_DIR}")
    target_include_directories(${TARGET} PRIVATE ${ZLIB_INCLUDE_DIR})
    target_link_libraries(${TARGET} Zlib)

endfunction()

function(NugetIncludeRapid TARGET)

    FetchContent_Declare(
        RapidXML
        GIT_REPOSITORY "https://github.com/0x08088405/rapidxml.git"
        GIT_TAG "master"
    )
    FetchContent_MakeAvailable(RapidXML)

    # Check the actual path where the headers are installed
    set(RAPIDXML_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/rapidxml-src")

    # Make sure the path is valid
    if (EXISTS "${RAPIDXML_INCLUDE_DIR}/rapidxml.hpp")
        message(STATUS "RapidXML found at ${RAPIDXML_INCLUDE_DIR}")
    else()
        message(FATAL_ERROR "RapidXML headers not found! Expected at: ${RAPIDXML_INCLUDE_DIR}")
    endif()

    # Include and link dependencies
    message(STATUS "Linking ${TARGET} to ${RAPIDXML_INCLUDE_DIR}")
    target_include_directories(${TARGET} PRIVATE ${RAPIDXML_INCLUDE_DIR})

endfunction()

function(NugetIncludeGTest TARGET)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    )
    FetchContent_MakeAvailable(googletest)

    # Check the actual path where the headers are installed
    set(SOURCE_INCLUDE_DIR "${CMAKE_BINARY_DIR}/_deps/googletest-src")

    # Make sure the path is valid
    if (EXISTS "${SOURCE_INCLUDE_DIR}")
        message(STATUS "GTest found at ${SOURCE_INCLUDE_DIR}")
    else()
        message(FATAL_ERROR "GTest not found! Expected at: ${SOURCE_INCLUDE_DIR}")
    endif()

    # For some reason this does not appear to work for GTest
    # You need to actually add these yourself (PRIVATE appears to make no difference)
    target_link_libraries(${TARGET} PRIVATE GTest::gtest GTest::gtest_main)

endfunction()