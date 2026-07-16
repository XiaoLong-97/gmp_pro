
:: Source File: gmp_fac_generate_cfg_json.bat

@echo off
setlocal enabledelayedexpansion

:: Generate config files template.
python ./gmp_fac_generate_cfg_json.py

:: prepare gmp_file_generator


:: Get script dir
set SCRIPT_DIR=%~dp0
set TARGET_DIR=%SCRIPT_DIR%gmp_file_generator

:: Check if target folder is existed.
if not exist "%TARGET_DIR%" (
    mkdir "%TARGET_DIR%"
    if errorlevel 1 (
        echo Cannot create target dir£¡
        exit /b 1
    )
)


:: Copy file gmp_fac_generate_srcs_example2.bat -> gmp_fac_generate_src.bat
set SOURCE_FILE1=%SCRIPT_DIR%gmp_fac_generate_srcs_example2.bat
set TARGET_FILE1=%TARGET_DIR%\gmp_fac_generate_src.bat

if exist "%SOURCE_FILE1%" (
    copy "%SOURCE_FILE1%" "%TARGET_FILE1%" >nul
    if errorlevel 1 (
        echo error happened when copying %SOURCE_FILE1% to %TARGET_FILE1% £¡
        exit /b 1
    )
    echo [INFO] %SOURCE_FILE1% to %TARGET_FILE1%
) else (
    echo Source file %SOURCE_FILE1% is messing£¡
    exit /b 1
)


:: Copy file facility_cfg.json -> gmp_facility_cfg.json
set SOURCE_DIR2=%SCRIPT_DIR%json
set SOURCE_FILE2=%SOURCE_DIR2%\facility_cfg.json
set TARGET_FILE2=%TARGET_DIR%\gmp_facility_cfg.json

if exist "%SOURCE_FILE2%" (
    copy "%SOURCE_FILE2%" "%TARGET_FILE2%" >nul
    if errorlevel 1 (
        echo error happened when copying %SOURCE_FILE2% to %TARGET_FILE2% £¡
        exit /b 1
    )
    echo [INFO] %SOURCE_FILE2% to %TARGET_FILE2%
) else (
    echo Source file %SOURCE_FILE2% is messing£¡
    exit /b 1
)


:: Copy file gmp_fac_config_gui_example.bat -> gmp_fac_config_gui.bat
set SOURCE_FILE3=%SCRIPT_DIR%gmp_fac_config_gui_example.bat
set TARGET_FILE3=%TARGET_DIR%\gmp_fac_config_gui.bat

if exist "%SOURCE_FILE3%" (
    copy "%SOURCE_FILE3%" "%TARGET_FILE3%" >nul
    if errorlevel 1 (
        echo error happened when copying %SOURCE_FILE3% to %TARGET_FILE3% £¡
        exit /b 1
    )
    echo [INFO] %SOURCE_FILE3% to %TARGET_FILE3%
) else (
    echo Source file %SOURCE_FILE3% is messing!
    exit /b 1
)

echo gmp_file_generaytor for user is ready.
