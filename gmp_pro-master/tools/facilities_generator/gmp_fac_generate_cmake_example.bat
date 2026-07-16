:: This file should copy to your own project folder.
:: By runing this script you may get a cmake script @gmp_make_tool.cmake

@echo off

:: Record Script Path
set "SCRIPT_DIR=%~dp0"
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

:: Check Environment variable
if "%GMP_PRO_LOCATION%"=="" (
    echo Error: GMP_PRO_LOCATION environment variable is not set.
    exit /b 1
)

:: call cmake generator
python "%GMP_PRO_LOCATION%/tools/facilities_generator/gmp_fac_generate_cmake.py" %SCRIPT_DIR%/json/facility_cfg.json

echo generate script done.

@pause

