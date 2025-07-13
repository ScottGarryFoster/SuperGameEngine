@echo off
setlocal

rem Call CMake update with tools chain if we need vcpkg in future.
cmake -S . -B build -DENABLE_TESTS=ON

rem Clean filters or other post build steps
python ../../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/

python ../../../FatedQuest.Libraries/CMake/CreateShortcut.py build\SuperGenerator-WithTests.sln SuperGenerator.sln
python ../../../FatedQuest.Libraries/CMake/CreateShortcut.py Generate-With-Tests.bat Regenerate
pause