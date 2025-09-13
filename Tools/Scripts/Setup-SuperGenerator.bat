echo off

REM This will build and deploy SuperGenerator
REM It is the last script to run once the built folder has all the
REM built binaries in that the launcher uses.

REM Kill the SuperGenerator if it is running so that it can build.
call KillApplication.bat SuperGenerator.exe
if errorlevel 1 (
    echo Failed to kill SuperGenerator!
    exit /b 1
)

REM Build and Deploy 
call BuildAndDeploy-SuperGenerator.bat

pause