@echo off
setlocal enabledelayedexpansion

:: Check sudo 
>nul 2>&1 "%SYSTEMROOT%\system32\cacls.exe" "%SYSTEMROOT%\system32\config\system"
if "%errorlevel%" neq "0" (
    echo This script must be run as an administrator, in order to remove environment path.
    echo Please right-click on the script file and select "Run as administrator".
    pause
    exit /b
)

:: Check if environment GMP_PRO_LOCATION is existed
echo Checking if environment variable GMP_PRO_LOCATION exists...
set "ENV_VAR_EXISTS=0"
for /f "tokens=2 delims==" %%a in ('set GMP_PRO_LOCATION 2^>nul') do (
    set "ENV_VAR_EXISTS=1"
)

:: if enviroment existed, remove it.
if %ENV_VAR_EXISTS%==1 (
    echo Environment variable GMP_PRO_LOCATION exists.
    echo Deleting environment variable GMP_PRO_LOCATION...
    setx GMP_PRO_LOCATION "" /m
    echo Environment variable GMP_PRO_LOCATION has been deleted.
) else (
    echo Environment variable GMP_PRO_LOCATION does not exist.
    echo No action required.
)

pause