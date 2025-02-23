include(FetchContent)

# Function to filter out files in the directory
function(NugetInclude LIBRARY TARGET)
    if(EXCLUDE EQUAL "zlib")
        NugetIncludeZlib(TARGET)
    endif()
    if(EXCLUDE EQUAL "rapidxml")
        NugetIncludeRapid(TARGET)
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
    set(ZLIB_LIBRARY "${NUGET_ZLIB_DIR}/lib/zlibstatic.lib")

    # Include and link dependencies
    target_include_directories(TARGET PRIVATE ${ZLIB_INCLUDE_DIR})
    #target_link_libraries(TARGET ${ZLIB_LIBRARY})
    target_link_libraries(TARGET Zlib)

endfunction()


function(NugetIncludeRapid TARGET)

    FetchContent_Declare(
        RapidXML
        URL "https://www.nuget.org/api/v2/package/rapidxml/1.13"
        DOWNLOAD_NO_EXTRACT TRUE
    )
    FetchContent_MakeAvailable(RapidXML)

    # Manually set RapidXML paths from NuGet
    set(NUGET_PACKAGES_DIR "${CMAKE_BINARY_DIR}/packages")

    # Rapid
    set(NUGET_RAPIDXML_DIR "${NUGET_PACKAGES_DIR}/rapidxml.1.13/build/native")
    if (NOT EXISTS "${NUGET_RAPIDXML_DIR}")
        execute_process(
            COMMAND nuget install rapidxml -Version 1.13 -OutputDirectory ${NUGET_PACKAGES_DIR}
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
    endif()
    set(RAPIDXML_INCLUDE_DIR "${NUGET_RAPIDXML_DIR}/include")

    # Include and link dependencies
    target_include_directories(GamePackage PRIVATE ${RAPIDXML_INCLUDE_DIR})

endfunction()