$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $PSScriptRoot
$sourcePath = Join-Path $repoRoot 'csp/c28x_syscfg/iris_280039c_board/user/iris_peripheral.c'
$source = Get-Content -LiteralPath $sourcePath -Encoding utf8 -Raw

$expected = [ordered]@{
    PSU_KEY_DIGIT_1       = 15
    PSU_KEY_DIGIT_2       = 14
    PSU_KEY_DIGIT_3       = 22
    PSU_KEY_DIGIT_4       = 6
    PSU_KEY_DIGIT_5       = 5
    PSU_KEY_DIGIT_6       = 4
    PSU_KEY_DIGIT_7       = 19
    PSU_KEY_DIGIT_8       = 18
    PSU_KEY_DIGIT_9       = 17
    PSU_KEY_DIGIT_0       = 2
    PSU_KEY_DECIMAL       = 1
    PSU_KEY_CONFIRM       = 9
    PSU_KEY_EDIT_TOGGLE   = 7
    PSU_KEY_OUTPUT_TOGGLE = 16
    PSU_KEY_STEP_TOGGLE   = 3
    PSU_KEY_CLEAR_ENTRY   = 21
}

$actual = @{}
$matches = [regex]::Matches(
    $source,
    '(?m)^#define\s+(PSU_KEY_(?:DIGIT_[0-9]|DECIMAL|CONFIRM|EDIT_TOGGLE|OUTPUT_TOGGLE|STEP_TOGGLE|CLEAR_ENTRY))\s+(\d+)U\s*$'
)
foreach ($match in $matches) {
    $actual[$match.Groups[1].Value] = [int]$match.Groups[2].Value
}

if ($matches.Count -ne $expected.Count -or $actual.Count -ne $expected.Count) {
    throw "Expected exactly $($expected.Count) PSU key mappings, found $($matches.Count)."
}

foreach ($entry in $expected.GetEnumerator()) {
    if (-not $actual.ContainsKey($entry.Key)) {
        throw "Missing key mapping: $($entry.Key)"
    }

    if ($actual[$entry.Key] -ne $entry.Value) {
        throw "$($entry.Key) must map to key_id $($entry.Value), got $($actual[$entry.Key])"
    }
}

$assignedIds = @($actual.Values)
if (($assignedIds | Sort-Object -Unique).Count -ne $assignedIds.Count) {
    throw 'Each PSU key function must use a unique key_id.'
}

Write-Output 'PSU keymap checks passed.'
