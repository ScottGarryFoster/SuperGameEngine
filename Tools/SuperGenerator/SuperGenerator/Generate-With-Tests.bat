@echo off
setlocal
pushd "%~dp0"

rem Call CMake update with tools chain if we need vcpkg in future.
cmake -S . -B build -DENABLE_TESTS=ON

rem Clean filters or other post build steps
python ../../../FatedQuest.Libraries/CMake/PostBuildScripts.py build\

python ../../../FatedQuest.Libraries/CMake/RepathSolutionFile.py build\SuperGenerator-WithTests.sln SuperGenerator.sln --prefix build
python ../../../FatedQuest.Libraries/CMake/CreateShortcut.py Generate-With-Tests.bat Regenerate
endlocal