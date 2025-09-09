@echo off
setlocal

rem Call CMake including the Tools Chain.
cmake -B build 
python ../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/ --noconsole

python ../../FatedQuest.Libraries/CMake/CreateShortcut.py build\FatedSolution.sln FatedLauncher.sln
python ../../FatedQuest.Libraries/CMake/CreateShortcut.py Generate.bat Regenerate

endlocal