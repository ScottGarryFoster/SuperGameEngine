echo off

REM This will build, deploy and launch the FatedLauncher.
REM It is the last script to run once the built folder has all the
REM built binaries in that the launcher uses.

REM Kill the launcher if it is running so that it can build.
call KillApplication.bat FatedLauncher.exe
if errorlevel 1 (
    echo Failed to kill FatedLauncher!
    exit /b 1
)

REM Build and Deploy 
call BuildAndDeploy-FatedLauncher.bat

REM Launch the Launcher
call Launch-FatedLauncher.bat

REM pause