@echo off
setlocal

rem Some packages we get via vcpkg
rem Not needed for C Sharp

rem Call CMake including the Tools Chain.
cmake -B build -DENABLE_TOOLS=OFF -DENABLE_TESTS=OFF

rem Clean filters or other post build steps
python ../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/

rem Add a shortcut for easy navigation
python ../../FatedQuest.Libraries/CMake/CreateShortcut.py build\FatedLauncher.sln FatedLauncher.sln
pause