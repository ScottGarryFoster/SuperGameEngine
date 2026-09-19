@echo off
setlocal
pushd "%~dp0"

rem Call CMake including the Tools Chain.
cmake -B build 
python ../../FatedQuest.Libraries/CMake/PostBuildScripts.py build/ --noconsole

rem FatedLauncher project Resources.
python ../../FatedQuest.Libraries/CMake/CopyFilesScript.py FatedLauncher\Resources build\FatedLauncher true

python ../../FatedQuest.Libraries/CMake/RepathSolutionFile.py build\FatedSolution.sln FatedSolution.sln --prefix build
python ../../FatedQuest.Libraries/CMake/CreateShortcut.py Generate.bat Regenerate

popd
endlocal