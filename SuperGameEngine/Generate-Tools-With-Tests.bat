@echo off
setlocal

rem Some packages we get via vcpkg
call ..\FatedQuest.Libraries\cmake\EnsureVCPKGIsFound.bat
call build\vcpkg\vcpkg install minizip
call build\vcpkg\vcpkg install zlib
echo Current directory: %CD%

rem Call CMake including the Tools Chain.
cmake -B build -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%" -DCMAKE_PREFIX_PATH="%CD%\Build\vcpkg\installed\x64-windows" -DENABLE_TOOLS=ON -DENABLE_TESTS=ON

rem Clean filters or other post build steps
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