$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $PSScriptRoot
$sourcePath = Join-Path $repoRoot 'csp/c28x_syscfg/iris_280039c_board/user/iris_peripheral.c'
$source = Get-Content -Raw $sourcePath

if ($source -notmatch '#define\s+PSU_ENABLE_FPGA_LINK\s+0') {
    Write-Output 'ERROR: Iris_Node_Env must disable its project-local FPGA link.'
    exit 1
}

if ($source -notmatch '(?s)static void psu_sync_fpga\(void\).*?#if PSU_ENABLE_FPGA_LINK.*?SPI_writeReg') {
    Write-Output 'ERROR: FPGA synchronization must remain available behind the project-local feature flag.'
    exit 1
}

Write-Output 'PSU FPGA isolation checks passed.'
