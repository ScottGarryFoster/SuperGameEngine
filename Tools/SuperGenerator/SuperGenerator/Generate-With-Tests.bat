@echo off
setlocal

rem Call CMake update with tools chain if we need vcpkg in future.
cmake -S . -B build -DENABLE_TESTS=ON

rem Clean filters or other post build steps
python ../../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/
pause