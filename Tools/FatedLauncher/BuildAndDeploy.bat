@echo off
setlocal

REM ========= CONFIGURE THESE PATHS =========
set GENERATE_SCRIPT="Generate.bat"
set SOLUTION_PATH="%~dp0\build\FatedSolution.sln"
set CONFIGURATION=Release
set PLATFORM="x64"
set BUILD_OUTPUT="build\bin\Release"
set DEPLOY_PATH="..\..\built\FatedLauncher\Release"
REM Full MSBuild path (update depending on your VS installation)
set MSBUILD_EXE="C:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
REM ========================================

echo.
echo ==== Step 1: Running Generate.bat ====
call %GENERATE_SCRIPT%
if %errorlevel% neq 0 (
    echo Generate.bat failed!
    exit /b %errorlevel%
)

echo.
echo ==== Step 2: Clean old Release output ====
if exist %DEPLOY_PATH% (
    echo Deleting existing contents of %DEPLOY_PATH%...
    del /q %DEPLOY_PATH%\* >nul 2>&1
    for /d %%d in (%DEPLOY_PATH%\*) do rmdir /s /q "%%d"
) else (
    echo Release folder not found, creating it...
    mkdir %DEPLOY_PATH%
)

echo.
echo ==== Step 3: Building solution ====
%MSBUILD_EXE% %SOLUTION_PATH% /p:Configuration=%CONFIGURATION% /p:Platform=%PLATFORM% /m
if %errorlevel% neq 0 (
    echo Build failed!
    pause /b %errorlevel%
)

echo.
echo ==== Step 4: Copying build output ====
if exist %DEPLOY_PATH% (
    echo Cleaning existing deploy folder...
    rmdir /s /q %DEPLOY_PATH%
)

mkdir %DEPLOY_PATH%
xcopy %BUILD_OUTPUT%\* %DEPLOY_PATH%\ /s /e /y

if %errorlevel% neq 0 (
    echo Copy failed!
    pause /b %errorlevel%
) else (
    echo Build and deploy succeeded!
)

endlocal