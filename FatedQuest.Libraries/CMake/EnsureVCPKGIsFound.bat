@echo off

rem Define directories (used in cmake)
set BUILD_DIR=build
set VCPKG_DIR=%CD%\Build\vcpkg
set TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake

rem Ensure anything run in vcpkg is not carried over in to the main script.
setlocal

rem Create build directory if it doesn't exist
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

rem Move into the build directory
cd "%BUILD_DIR%"

rem Clone vcpkg if it does not exist
if not exist "%VCPKG_DIR%" (
    git clone https://github.com/microsoft/vcpkg.git "%VCPKG_DIR%"
)

rem Ensure vcpkg.exe exists
if not exist "%VCPKG_DIR%\vcpkg.exe" (
    cd "%VCPKG_DIR%"
    call bootstrap-vcpkg.bat
    cd ..
)

endlocal