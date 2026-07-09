@echo off
setlocal

:: Default build configuration
set "CXX=g++"
set "CXXFLAGS=-std=c++23 -O2 -Wall -Wextra"

:: Load .env overrides if present
if exist ".env" (
    if not exist "tmp" mkdir "tmp"

    REM Generate a temporary batch file with set commands parsed from .env.
    REM PowerShell is used because cmd has no robust .env parser.
    REM The regex supports optional "export" prefix and strips surrounding quotes.
    REM [char]34 is used to avoid cmd double-quote escaping issues.
    powershell -NoProfile -ExecutionPolicy Bypass -Command "Get-Content '.env' | ForEach-Object { $line = $_.Trim(); if ($line -match '^\s*(?:export\s+)?([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(.*)$') { $k = $matches[1].Trim(); $v = $matches[2].Trim(); if ($v.Length -ge 2 -and $v[0] -eq 34 -and $v[-1] -eq 34) { $v = $v.Substring(1, $v.Length - 2) } $q = [char]34; Write-Output ('set ' + $q + $k + '=' + $v + $q) } }" > "tmp\env.bat"

    if exist "tmp\env.bat" (
        call "tmp\env.bat"
        del "tmp\env.bat"
    )
)

:: Input/output files
set "INPUT=input.txt"
set "OUTPUT=output.txt"
if not "%~1"=="" set "INPUT=%~1"
if not "%~2"=="" set "OUTPUT=%~2"

set "BUILD_DIR=tmp"
set "EXE=%BUILD_DIR%\main.exe"

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"

:: Ensure the compiler's directory is in PATH so it can find its DLLs.
for %%i in ("%CXX%") do set "CXX_DIR=%%~dpi"
set "PATH=%CXX_DIR%;%PATH%"

echo [%CXX%] %CXXFLAGS% -o "%EXE%" main.cpp
"%CXX%" %CXXFLAGS% -o "%EXE%" main.cpp
if %ERRORLEVEL% neq 0 exit /b %ERRORLEVEL%

echo "%EXE%" ^< "%INPUT%" ^> "%OUTPUT%"
"%EXE%" < "%INPUT%" > "%OUTPUT%"
