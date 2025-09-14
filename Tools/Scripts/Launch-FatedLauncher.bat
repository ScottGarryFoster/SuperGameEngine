@echo off
setlocal
pushd "%~dp0..\FatedLauncher\build\bin\Release"
start "" FatedLauncher.exe
popd
endlocal