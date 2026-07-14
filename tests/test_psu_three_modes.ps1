$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $PSScriptRoot
$userRoot = Join-Path $repoRoot 'csp/c28x_syscfg/iris_280039c_board/user'
$headerPath = Join-Path $userRoot 'psu_mode_control.h'
$sourcePath = Join-Path $userRoot 'iris_peripheral.c'
$calibrationPath = Join-Path $userRoot 'psu_calibration.h'

if (-not (Test-Path -LiteralPath $headerPath)) {
    throw 'Missing psu_mode_control.h three-mode policy.'
}

$header = Get-Content -LiteralPath $headerPath -Encoding utf8 -Raw
$source = Get-Content -LiteralPath $sourcePath -Encoding utf8 -Raw
$calibration = Get-Content -LiteralPath $calibrationPath -Encoding utf8 -Raw

$requiredHeaderPatterns = [ordered]@{
    'AUTO mode constant' = '#define\s+PSU_INPUT_MODE_AUTO\s+0U'
    'CV mode constant' = '#define\s+PSU_INPUT_MODE_CV\s+1U'
    'CC mode constant' = '#define\s+PSU_INPUT_MODE_CC\s+2U'
    'CV current compliance' = '#define\s+PSU_MODE_CURRENT_COMPLIANCE_MA\s+105U'
    'CC voltage compliance' = '#define\s+PSU_MODE_VOLTAGE_COMPLIANCE_MV\s+10000U'
    'mode cycle helper' = 'psu_mode_next_input\s*\('
    'edit permission helper' = 'psu_mode_allowed_edit\s*\('
    'voltage target helper' = 'psu_mode_voltage_target_mv\s*\('
    'current target helper' = 'psu_mode_current_target_ma\s*\('
    'safe switch helper' = 'psu_mode_switch\s*\('
}

foreach ($entry in $requiredHeaderPatterns.GetEnumerator()) {
    if ($header -notmatch $entry.Value) {
        throw "Missing $($entry.Key) in psu_mode_control.h."
    }
}

$requiredSourcePatterns = [ordered]@{
    'mode policy include' = '#include\s+"psu_mode_control\.h"'
    'SW18 mode mapping' = '#define\s+PSU_KEY_MODE_TOGGLE\s+20U'
    'input mode state' = 'uint16_t\s+input_mode\s*;'
    'regulation state' = 'uint16_t\s+regulation_state\s*;'
    'mode key handler' = 'case\s+PSU_KEY_MODE_TOGGLE\s*:'
    'mode switch action' = 'psu_switch_input_mode\s*\(\s*\)'
    'safe output assignment' = 'psu_ui\.output_on\s*=\s*\(fast_gt\)switched\.output_on'
    'pure mode edit lock' = 'if\s*\(\s*psu_ui\.input_mode\s*!=\s*PSU_INPUT_MODE_AUTO\s*\)[\s\S]*?return\s*;'
    'voltage DAC policy' = 'psu_mode_voltage_target_mv\s*\(\s*psu_ui\.input_mode'
    'current DAC policy' = 'psu_mode_current_target_ma\s*\(\s*psu_ui\.input_mode'
    'AUTO display' = 'AUTO-%s'
    'released key edge reset' = 'if\s*\(\s*key_id\s*==\s*0\s*\)[\s\S]*last_key_id\s*=\s*0'
}

foreach ($entry in $requiredSourcePatterns.GetEnumerator()) {
    if ($source -notmatch $entry.Value) {
        throw "Missing $($entry.Key) integration in iris_peripheral.c."
    }
}

if ($calibration -notmatch '#define\s+PSU_CALIBRATION_VOLTAGE_TARGET_MAX_MV\s+10000U') {
    throw 'Calibration command range must include the 10.0 V CC compliance target.'
}

if ($calibration -notmatch '#define\s+PSU_CALIBRATION_CURRENT_TARGET_MAX_MA\s+105U') {
    throw 'Calibration command range must include the 105 mA CV compliance target.'
}

if ($source -match 'PSU_MODE_CV|PSU_MODE_CC') {
    throw 'Legacy mixed-purpose PSU_MODE_CV/PSU_MODE_CC state is still present.'
}

Write-Output 'PSU three-mode integration checks passed.'
