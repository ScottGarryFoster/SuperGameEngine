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

function(NugetIncludeSdl2 TARGET)

    FetchContent_Declare(
        SDL2
        URL "https://www.nuget.org/api/v2/package/sdl2.nuget/2.30.9"
    )
    FetchContent_MakeAvailable(SDL2)

    # Manually set RapidXML paths from NuGet
    set(NUGET_PACKAGES_DIR "${CMAKE_BINARY_DIR}/packages")

    # SDL2
    set(NUGET_SDL2_DIR "${NUGET_PACKAGES_DIR}/sdl2.nuget.2.30.9/build/native")
    if (NOT EXISTS "${NUGET_SDL2_DIR}")
        execute_process(
            COMMAND nuget install sdl2 -Version 2.30.9 -OutputDirectory ${NUGET_PACKAGES_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()

    # Grab the Library paths
    set(SDL2_NATIVE "${CMAKE_BINARY_DIR}/_deps/sdl2-src/build/native")
    set(SDL2_INCLUDE_DIR "${SDL2_NATIVE}/include")

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH_DIR "x64")
    else()
        set(ARCH_DIR "Win32")
    endif()

    set(SDL2_LIB_DIR "${SDL2_NATIVE}/lib/${ARCH_DIR}")

    # Nothing checks to see if these are empty or non-existant we need to check
    if (NOT EXISTS "${SDL2_NATIVE}")
        message(FATAL_ERROR "SDL2 (Main) Source Files not found: ${SDL2_NATIVE}")
    endif()

    if (NOT EXISTS "${SDL2_INCLUDE_DIR}")
        message(FATAL_ERROR "SDL2 (Main) Source Files not found: ${SDL2_INCLUDE_DIR}")
    endif()

    if (NOT EXISTS "${SDL2_LIB_DIR}")
        message(FATAL_ERROR "SDL2 (Main) Source Files not found: ${SDL2_LIB_DIR}")
    endif()

    # Include and link dependencies
    message(STATUS "Linking ${TARGET} to ${SDL2_INCLUDE_DIR}")
    target_include_directories(${TARGET} PRIVATE ${SDL2_INCLUDE_DIR})
    target_link_libraries(${TARGET} ${SDL2_LIB_DIR})

endfunction()

function(NugetIncludeSdl2Image TARGET)

    FetchContent_Declare(
        SDL2_image
        URL "https://www.nuget.org/api/v2/package/sdl2_image.nuget/2.8.2"
    )
    FetchContent_MakeAvailable(SDL2_image)

    # Manually set RapidXML paths from NuGet
    set(NUGET_PACKAGES_DIR "${CMAKE_BINARY_DIR}/packages")

    # SDL2
    set(NUGET_SDL2_DIR "${NUGET_PACKAGES_DIR}/sdl2_image.nuget.2.8.2/build/native")
    if (NOT EXISTS "${NUGET_SDL2_DIR}")
        execute_process(
            COMMAND nuget install sdl2_image -Version 2.8.2 -OutputDirectory ${NUGET_PACKAGES_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()

    # Grab the Library paths
    set(SDL2_NATIVE "${CMAKE_BINARY_DIR}/_deps/sdl2_image-src/build/native")
    set(SDL2_INCLUDE_DIR "${SDL2_NATIVE}/include")

    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH_DIR "x64")
    else()
        set(ARCH_DIR "Win32")
    endif()

    set(SDL2_LIB_DIR "${SDL2_NATIVE}/lib/${ARCH_DIR}")

    # Nothing checks to see if these are empty or non-existant we need to check
    if (NOT EXISTS "${SDL2_NATIVE}")
        message(FATAL_ERROR "SDL2 Image Source Files not found: ${SDL2_NATIVE}")
    endif()

    if (NOT EXISTS "${SDL2_INCLUDE_DIR}")
        message(FATAL_ERROR "SDL2 Image Source Files not found: ${SDL2_INCLUDE_DIR}")
    endif()

    if (NOT EXISTS "${SDL2_LIB_DIR}")
        message(FATAL_ERROR "SDL2 Image Source Files not found: ${SDL2_LIB_DIR}")
    endif()

    # Include and link dependencies
    message(STATUS "Linking ${TARGET} to ${SDL2_INCLUDE_DIR}")
    target_include_directories(${TARGET} PRIVATE ${SDL2_INCLUDE_DIR})
    target_link_libraries(${TARGET} ${SDL2_LIB_DIR})

endfunction()

function(NugetIncludeSdl2Mixer TARGET)

    FetchContent_Declare(
        SDL2_mixer
        URL "https://www.nuget.org/api/v2/package/sdl2_mixer.nuget/2.8.0"
    )
    FetchContent_MakeAvailable(SDL2_mixer)

    # Manually set RapidXML paths from NuGet
    set(NUGET_PACKAGES_DIR "${CMAKE_BINARY_DIR}/packages")

    # SDL2
    set(NUGET_SDL2_DIR "${NUGET_PACKAGES_DIR}/sdl2_mixer.nuget.2.8.0/build/native")
    if (NOT EXISTS "${NUGET_SDL2_DIR}")
        execute_process(
            COMMAND nuget install sdl2_mixer -Version 2.8.0 -OutputDirectory ${NUGET_PACKAGES_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()

    # Grab the Library paths
    set(SDL2_NATIVE "${CMAKE_BINARY_DIR}/_deps/sdl2_mixer-src/build/native")
    set(SDL2_INCLUDE_DIR "${SDL2_NATIVE}/include")
    
    if(CMAKE_SIZEOF_VOID_P EQUAL 8)
        set(ARCH_DIR "x64")
    else()
        set(ARCH_DIR "Win32")
    endif()

    set(SDL2_LIB_DIR "${SDL2_NATIVE}/lib/${ARCH_DIR}")

    # Nothing checks to see if these are empty or non-existant we need to check
    if (NOT EXISTS "${SDL2_NATIVE}")
        message(FATAL_ERROR "SDL2 Mixer Source Files not found: ${SDL2_NATIVE}")
    endif()

    if (NOT EXISTS "${SDL2_INCLUDE_DIR}")
        message(FATAL_ERROR "SDL2 Mixer Source Files not found: ${SDL2_INCLUDE_DIR}")
    endif()

    if (NOT EXISTS "${SDL2_LIB_DIR}")
        message(FATAL_ERROR "SDL2 Mixer Source Files not found: ${SDL2_LIB_DIR}")
    endif()

    # Include and link dependencies
    message(STATUS "Linking ${TARGET} to ${SDL2_INCLUDE_DIR}")
    target_include_directories(${TARGET} PRIVATE ${SDL2_INCLUDE_DIR})
    target_link_libraries(${TARGET} ${SDL2_LIB_DIR})

endfunction()