@echo off
setlocal
pushd "%~dp0"

rem Call CMake including the Tools Chain.
cmake -B build 
python ../../FatedQuest.Libraries/CMake/PostBuildScripts.py %~dp0/build/ --noconsole

python ../../FatedQuest.Libraries/CMake/CreateShortcut.py %~dp0\build\FatedSolution.sln %~dp0\FatedLauncher.sln
python ../../FatedQuest.Libraries/CMake/CreateShortcut.py %~dp0\Generate.bat %~dp0\Regenerate

popd
endlocal