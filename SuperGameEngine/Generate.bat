@echo off
setlocal

rem Define directories
set BUILD_DIR=build
set VCPKG_DIR=%CD%\Build\vcpkg
set TOOLCHAIN_FILE=%VCPKG_DIR%\scripts\buildsystems\vcpkg.cmake

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

call vcpkg\vcpkg install minizip
call vcpkg\vcpkg install zlib

rem Run CMake with vcpkg toolchain
cmake -S .. -B . -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%" -DCMAKE_PREFIX_PATH="%CD%\Build\vcpkg\installed\x64-windows"

rem Move one folder out
cd ..

python ../FatedQuest.Libraries/CMake/PostBuildScripts.py build/

Rem Copy Runtime SDL2
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2redistnuget-src\build\native\bin\x64 build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2redistnuget-src\build\native\bin\x64 build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2redistnuget-src\build\native\bin\x64 build\SuperGameEngine\Tools_Debug false

Rem Copy Runtime SDL2 Image
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2imageredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2imageredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2imageredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Tools_Debug false

Rem Copy Runtime SDL2 Mixer
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2mixerredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2mixerredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\_deps\sdl2mixerredistnuget-src\build\native\bin\x64 build\SuperGameEngine\Tools_Debug false

Rem Copy Runtime Zlib
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\SuperGameEngine\Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\SuperGameEngine\Debug false

python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\SuperGameEngine\Tools_Debug false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\SuperGameEngine\Tools_Debug false

python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\SuperGameEngine\Release false
python ../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\SuperGameEngine\Release false


pause