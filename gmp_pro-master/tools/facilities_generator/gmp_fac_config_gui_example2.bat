:: Source file: gmp_fac_config_gui_example.bat


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
python "%GMP_PRO_LOCATION%/tools/facilities_generator/gmp_fac_config_gui.py" %SCRIPT_DIR%/json/facility_cfg.json

echo config script done.

