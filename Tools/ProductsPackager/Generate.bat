@echo off
setlocal

rem Some packages we get via vcpkg
call ..\..\FatedQuest.Libraries\cmake\EnsureVCPKGIsFound.bat
call build\vcpkg\vcpkg install minizip
call build\vcpkg\vcpkg install zlib
echo Current directory: %CD%

rem Call CMake including the Tools Chain.
cmake -B build -DCMAKE_TOOLCHAIN_FILE="%TOOLCHAIN_FILE%" -DCMAKE_PREFIX_PATH="%CD%\Build\vcpkg\installed\x64-windows"

rem Clean filters or other post build steps
python ../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/

Rem Copy Runtime Zlib
python ../../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\ProductsPackager\Debug false
python ../..//FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\ProductsPackager\Debug false

python ../../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\ProductsPackager\Release false
python ../../FatedQuest.Libraries/CMake/CopyFilesScript.py build\vcpkg\installed\x64-windows\bin build\ProductsPackager\Release false
pause