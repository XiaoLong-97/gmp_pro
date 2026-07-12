$ErrorActionPreference = 'Stop'

$project = Join-Path $PSScriptRoot '..\csp\c28x_syscfg\iris_280039c_board'
$files = @(
    (Join-Path $project 'user\ctl_main.c'),
    (Join-Path $project 'user\ctl_main.h'),
    (Join-Path $project 'user\user_main.c'),
    (Join-Path $project 'xplt\xplt.ctl_interface.h'),
    (Join-Path $project 'xplt\xplt.peripheral.c')
)

$forbidden = @(
    'dac_a_lead',
    'dac_a_pu',
    'tsk_lead_param_update',
    'ctl_step_lead',
    'ctl_step_pwm_channel',
    'tsk_dl_debug_device',
    'tsk_blink',
    'gmp_pil_sim_init',
    'gmp_param_tunable_init',
    'gmp_mem_persp_init',
    'gmp_base_ctl_step'
)

$matches = Select-String -Path $files -Pattern $forbidden -SimpleMatch
if ($matches) {
    $matches | ForEach-Object {
        Write-Error ("Training residue: {0}:{1}: {2}" -f $_.Path, $_.LineNumber, $_.Line.Trim())
    }
}

Write-Output 'No training-task runtime residue found.'
