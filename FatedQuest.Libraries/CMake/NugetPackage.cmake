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
    if(${LIBRARY} STREQUAL "sdl2")
        NugetIncludeSdl2(${TARGET})
    endif()
    if(${LIBRARY} STREQUAL "sdl2Image")
        NugetIncludeSdl2Image(${TARGET})
    endif()
    if(${LIBRARY} STREQUAL "sdl2Mixer")
        NugetIncludeSdl2Mixer(${TARGET})
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
    target_link_libraries(${TARGET} PRIVATE Zlib)

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

function(NugetIncludeSdl2 TARGET)

    FetchContent_Declare(
    SDL2NuGet
        URL https://www.nuget.org/api/v2/package/sdl2.nuget/2.30.9
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(SDL2NuGet)

    set(SDL2NuGet_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/sdl2nuget-src")
    message("SDL ${SDL2NuGet_SOURCE_DIR}")

    # Find the extracted SDL2 files
    set(SDL2_BASE_DIR "${SDL2NuGet_SOURCE_DIR}")
    set(SDL2_INCLUDE_DIR "${SDL2_BASE_DIR}/build/native/include")
    set(SDL2_LIB_DIR "${SDL2_BASE_DIR}/build/native/lib/x64")

    if(NOT TARGET SDL2)
        add_library(SDL2 STATIC IMPORTED)
        set_target_properties(SDL2 PROPERTIES
            IMPORTED_LOCATION "${SDL2_LIB_DIR}/SDL2.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL2_INCLUDE_DIR}"
        )
    endif()

    target_link_libraries(${TARGET} PRIVATE SDL2)

endfunction()

function(NugetIncludeSdl2Image TARGET)

    FetchContent_Declare(
        SDL2ImageNuGet
        URL https://www.nuget.org/api/v2/package/sdl2_image.nuget/2.8.2
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(SDL2ImageNuGet)

    set(SDL2ImageNuGet_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/sdl2imagenuget-src")

    set(SDL2_IMAGE_BASE_DIR "${SDL2ImageNuGet_SOURCE_DIR}/build/native")
    set(SDL2_IMAGE_INCLUDE_DIR "${SDL2_IMAGE_BASE_DIR}/include")
    set(SDL2_IMAGE_LIB_DIR "${SDL2_IMAGE_BASE_DIR}/lib/x64")

    # Create SDL2_image target
    if(NOT TARGET SDL2_image)
        add_library(SDL2_image STATIC IMPORTED)
        set_target_properties(SDL2_image PROPERTIES
            IMPORTED_LOCATION "${SDL2_IMAGE_LIB_DIR}/SDL2_image.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL2_IMAGE_INCLUDE_DIR}"
        )
    endif()

    target_link_libraries(${TARGET} PRIVATE SDL2_image)

endfunction()

function(NugetIncludeSdl2Mixer TARGET)

    # SDL2_mixer
    FetchContent_Declare(
        SDL2MixerNuGet
        URL https://www.nuget.org/api/v2/package/sdl2_mixer.nuget/2.8.0
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    )
    FetchContent_MakeAvailable(SDL2MixerNuGet)

    set(SDL2MixerNuGet_SOURCE_DIR "${CMAKE_BINARY_DIR}/_deps/sdl2mixernuget-src")
    set(SDL2_MIXER_BASE_DIR "${SDL2MixerNuGet_SOURCE_DIR}/build/native")
    set(SDL2_MIXER_INCLUDE_DIR "${SDL2_MIXER_BASE_DIR}/include")
    set(SDL2_MIXER_LIB_DIR "${SDL2_MIXER_BASE_DIR}/lib/x64")

    # Create SDL2_mixer target
    if(NOT TARGET SDL2_mixer)
        add_library(SDL2_mixer STATIC IMPORTED)
        set_target_properties(SDL2_mixer PROPERTIES
            IMPORTED_LOCATION "${SDL2_MIXER_LIB_DIR}/SDL2_mixer.lib"
            INTERFACE_INCLUDE_DIRECTORIES "${SDL2_MIXER_INCLUDE_DIR}"
        )
    endif()

    target_link_libraries(${TARGET} PRIVATE SDL2_mixer)
endfunction()