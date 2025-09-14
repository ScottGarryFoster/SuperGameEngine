@echo off
setlocal
pushd "%~dp0"
call ScriptVariables.bat

REM This will build and deploy SuperGenerator to the built binary location.

REM ========= CONFIGURE THESE PATHS =========
set GENERATE_SCRIPT="..\SuperGenerator\SuperGenerator\Generate.bat"
set SOLUTION_PATH="..\SuperGenerator\SuperGenerator\build\SuperGenerator.sln"
set CONFIGURATION=Release
set PLATFORM="x64"
set BUILD_OUTPUT="..\SuperGenerator\SuperGenerator\build\SuperGenerator\Release"
set DEPLOY_PATH="..\..\built\SuperGenerator\Release"
REM ========================================

REM Build the basic generation script
call %GENERATE_SCRIPT%
if %errorlevel% neq 0 (
    echo Generate.bat failed!
    exit /b %errorlevel%
)

REM Remove old deploy folder
if exist %DEPLOY_PATH% (
    echo Deleting existing contents of %DEPLOY_PATH%...
    del /q %DEPLOY_PATH%\* >nul 2>&1
    for /d %%d in (%DEPLOY_PATH%\*) do rmdir /s /q "%%d"
) else (
    echo Release folder not found, creating it...
    mkdir %DEPLOY_PATH%
)

REM Kick off the solution build
%VAR_MSBUILD_EXE% %SOLUTION_PATH% /p:Configuration=%CONFIGURATION% /p:Platform=%PLATFORM% /m
if %errorlevel% neq 0 (
    echo Build failed!
    pause /b %errorlevel%
)

REM Double check the folder is definately empty
if exist %DEPLOY_PATH% (
    echo Cleaning existing deploy folder...
    rmdir /s /q %DEPLOY_PATH%
)

REM Copy the binary to built
mkdir %DEPLOY_PATH%
xcopy %BUILD_OUTPUT%\* %DEPLOY_PATH%\ /s /e /y

if %errorlevel% neq 0 (
    echo Copy failed!
    pause /b %errorlevel%
) else (
    echo Build and deploy succeeded!
)

popd
endlocal