@echo off
setlocal
pushd "%~dp0"

REM If running this on a new machine check ScriptVariables.bat to see
REM the variables make sense such as the Build variables.

call Setup-SuperGenerator.bat

REM Launcher needs to be last as it runs the application and checks for
REM the existance of the above.
call Setup-FatedLauncher.bat

popd
endlocal