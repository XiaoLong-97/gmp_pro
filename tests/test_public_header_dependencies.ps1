$ErrorActionPreference = 'Stop'

$repoRoot = Split-Path -Parent $PSScriptRoot

$expectations = @(
    @{
        Path = 'ctl/component/digital_power/inv/pll_ddsrf.h'
        Includes = @(
            '#include <ctl/component/intrinsic/discrete/discrete_filter.h>',
            '#include <ctl/math_block/coordinate/coord_trans.h>'
        )
    },
    @{
        Path = 'ctl/component/digital_power/sinv/spll_sogi.h'
        Includes = @('#include <ctl/component/intrinsic/discrete/discrete_filter.h>')
    },
    @{
        Path = 'ctl/component/digital_power/sinv/spll_sogi_dc.h'
        Includes = @('#include <ctl/component/intrinsic/discrete/discrete_filter.h>')
    },
    @{
        Path = 'ctl/component/motor_control/basic/mtr_protection.h'
        Includes = @('#include <ctl/component/interface/interface_base.h>')
    }
)

$failures = @()
foreach ($expectation in $expectations) {
    $fullPath = Join-Path $repoRoot $expectation.Path
    $content = Get-Content -Raw $fullPath
    foreach ($include in $expectation.Includes) {
        if (-not $content.Contains($include)) {
            $failures += "$($expectation.Path) must directly declare dependency: $include"
        }
    }
}

if ($failures.Count -gt 0) {
    $failures | ForEach-Object { Write-Output "ERROR: $_" }
    exit 1
}

Write-Output 'Public header dependency checks passed.'
