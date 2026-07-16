@echo off
setlocal EnableDelayedExpansion

:: 检查环境变量GMP_PRO_LOCATION是否已设置
if not defined GMP_PRO_LOCATION (
    echo The environment variable GMP_PRO_LOCATION is not set.
    exit /b
)

:: 获取环境变量GMP_PRO_LOCATION的值
set "targetDir=%GMP_PRO_LOCATION%"

:: 删除所有.metadata文件夹
for /d /r "%targetDir%" %%d in (.metadata) do (
    if exist "%%d" (
        rmdir /s /q "%%d"
        echo Deleted .metadata folder: "%%d"
    ))
    ::) else (
        ::echo .
    ::)
::)

:: 删除所有.meta文件夹
for /d /r "%targetDir%" %%d in (.meta) do (
    if exist "%%d" (
        rmdir /s /q "%%d"
        echo Deleted .meta folder: "%%d"
    ))
    ::) else (
        ::echo .
    ::)
::)

echo Cleanup complete.
endlocal

@pause
