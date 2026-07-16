# GMP CTL PMSM Motor Control Suite

PMSM id = 0 controller.

## Abstract

BOOSTXL-3PHGANINV (48-V Three-Phase Inverter With Shunt-Based In-Line Motor Phase Current Sensing Evaluation Module) is used to implement a Motor Driver. You may find related notes here: https://www.ti.com/tool/BOOSTXL-3PHGANINV

### Current & Voltage Measurement 

1. Current Measurement

Current Measurement using a $0.005 \,\Omega$ resister, and INA240A1 provide 20 gain.

2. Voltage Measurement

Voltage Measurement gain is 
$$
A_v = \frac{4.22 \,k\Omega}{100 \,k\Omega + 4.22 \,k\Omega} = 0.04049127
$$


Meanwhile, Voltage filter is cut frequency is 
$$
f_{vc} = \frac{1}{2\pi RC}=\frac{1}{2\pi \times 4.22 \,k\Omega \times 0.033 \,\mu F}= 1.1434\,kHz
$$

3. Motor Parameters

The target motor is a PMSM motor, which parameter is stored in  `ctl/component/motor_control/preset_motor_param/GBM2804H_100T.h`



## Encoder Hardware

The system use [AS5048A](https://docs.rs-online.com/0657/A700000006921305.pdf) as absolute position encoder. This is a 14-bit rotary position sensor with SPI interface. 



## Software Structure

GMP CTL motor_control suite owns a PMSM controller with absolute position encoder based on CTL nano framework. Main parts is defined in `pmsm_servo.h`, some initialization code is defined in `src/pmsm_servo.c` .

A set of invoke examples is defined in `implement` folder. `impelement/user_common` owns basic usage of `pmsm_servo`, and these code are unrelated to MCU. Other code related with running platform is defined in each folder.

| Folder        | Platform                                                     |
| ------------- | ------------------------------------------------------------ |
| user_f28x     | [Launch Pad F280039](https://www.ti.com/tool/LAUNCHXL-F280039C) |
| user_simulink | GMP SIL                                                      |
| user_stm32    | [NUCLEO-G474RE](https://www.st.com/en/evaluation-tools/nucleo-g474re.html) |



 You may change motor config in `impelement/<platform>/ctrl_settings.h`.

| MACROS                   | Notes                                                    |
| ------------------------ | -------------------------------------------------------- |
| BUILD_LEVEL              | Select Build Level. Open loop, Current loop, Speed loop. |
| CONTROLLER_FREQUENCY     | Select Controller Frequency.                             |
| CONTROLLER_PWM_CMP_MAX   | 比较器最大值                                             |
| MTR_ENCODER_LINES        | 编码器线数                                               |
| MTR_ENCODER_OFFSET       | 编码器偏置                                               |
| MTR_CTRL_CURRENT_LOOP_BW | 控制器电流带宽                                           |
| MTR_CTRL_SPEED_LOOP_BW   | 控制器速度带宽                                           |

控制器参数还通过电机预设和控制器预设读入。

``` C
// invoke motor parameters
#include <ctl/component/motor_control/motor_preset/GBM2804H_100T.h>

// invoke motor controller parameters
#include <ctl/component/motor_control/controller_preset/TI_3PH_GAN_INV.h>
```
下一步计划：增加弱磁控制的代码




## GMP SIL Simulation Environment

GMP SIL Project: `gmp_pro\ctl\suite\motor_control\pmsm\projects\motor_control_simulink`

You may open the `motor_control_simulink.sln` using Visual Studio 2022, and `gmp_pmsm_sil_mdl.slx` using MATLAB Simulink 2024 or later.

> NOTICE: 
>
>  If you have not install GMP CTL Simulink Library, you should install this library firstly, by running `gmp_pro\slib\install_gmp_simulink_lib.m`

You should run Visual Studio Solution firstly, and then run the simulation model.

 You may change `ctl_fmif_output_stage_routine` function in `implement\user_simulink\ctl_interface.h`monitor routine to spy on the key variables.



## C28x Motor Control Environment

Project Location: `gmp_pro\ctl\suite\motor_control\pmsm\projects\motor_control_c28x_example`

You may import the project by CCS12.

If there're some product don't exist, you should run `gmp_pro\tools\facilities_generator\gmp_fac_install.bat`to install these TI CCS product.

device peripheral config

Encoder SPI port, Mode 

| Signal          | Peripheral | GPIO Index |
| --------------- | ---------- | ---------- |
| SPI CS          | GPIO       | GPIO48     |
| SPI SIMO (PICO) | SPIA       | GPIO8      |
| SPI SOMI (POCI) | SPIA       | GPIO17     |
| SPI CLK         | SPIA       | GPIO9      |

print SCI port, baud rate 115200 bps

| Signal  | Peripheral | GPIO Index |
| ------- | ---------- | ---------- |
| SCIA RX | SCIA       | GPIO28     |
| SCIA TX | SCIA       | GPIO29     |

EPWM channel, 10 kHz PWM

| Signal  | Peripheral | GPIO index |
| ------- | ---------- | ---------- |
| PWM U H | ePWM1      | GPIO0      |
| PWM U L | ePWM1      | GPIO1      |
| PWM V H | ePWM2      | GPIO2      |
| PWM V L | ePWM2      | GPIO3      |
| PWM W H | ePWM6      | GPIO10     |
| PWM W L | ePWM6      | GPIO11     |

Calculate Time Base period
$$
Period = \frac{120 \,MHz}{10\,kHz\times 2}=6000
$$

ADC Channel, ADCA for U phase, ADCB for V phase, ADCC for W phase, all of them is high priority.

| Signal | Peripheral | ADC Channel |
| ------ | ---------- | ----------- |
| VDC    | ADC A      | ADC A6      |
| VA     | ADC A      | ADC A2      |
| VB     | ADC B      | ADC B9      |
| VC     | ADC C      | ADC C4      |
| IA     | ADC A      | ADC A11     |
| IB     | ADC B      | ADC B12     |
| IC     | ADC C      | ADC C3      |



## STM32G474 Motor Control Environment

Project Location: `gmp_pro\ctl\suite\motor_control\pmsm\projects\motor_control_stm32g474_hrtim`

You may edit this project with STM32 CubeMX and Open the project using Keil. Keil will generate GMP files every compiling time.

Encoder SPI Interface

| Signal   | Peripheral | GPIO     |
| -------- | ---------- | -------- |
| SPI CS   | SPI2       | GPIO B10 |
| SPI SIMO | SPI2       | GPIO B15 |
| SPI SOMI | SPI2       | GPIO B14 |
| SPI CLK  | SPI2       | GPIO B13 |

print USART interface, connected by Debugger.

| Signal    | Peripheral | GPIO |
| --------- | ---------- | ---- |
| USART1 TX | USART1     | PA2  |
| USART1 RX | USART1     | PA3  |

HRTIM PWM channel

| Signal       | Peripheral     | Application  | GPIO |
| ------------ | -------------- | ------------ | ---- |
| PWM Phase UH | HRTIM Timer E1 | PWM Phase UH | PC8  |
| PWM Phase UL | HRTIM Timer E2 | PWM Phase UL | PC9  |
| PWM Phase VH | HRTIM Timer A1 | PWM Phase VH | PA8  |
| PWM Phase VL | HRTIM Timer A2 | PWM Phase VL | PA9  |
| PWM Phase WH | HRTIM Timer B1 | PWM Phase WH | PA10 |
| PWM Phase WL | HRTIM Timer B2 | PWM Phase WL | PA11 |

ADC Resources

| Signal | Peripheral      | GPIO |
| ------ | --------------- | ---- |
| IA     | ADC1 Channel 1  | PA0  |
| VA     | ADC1 Channel 2  | PA1  |
| IB     | ADC2 Channel 3  | PA6  |
| VB     | ADC2 Channel 3  | PA7  |
| VDC    | ADC2 Channel 12 | PB2  |
| IC     | ADC3 Channel 12 | PB0  |
| VC     | ADC3 Channel 1  | PB1  |

User interface 

| Signal      | Usage       | GPIO |
| ----------- | ----------- | ---- |
| User Button | GPIO Input  | PC13 |
| User LED    | GPIO Output | PA5  |



## STM32G431 Motor Control Environment



project path: `gmp_pro\ctl\suite\motor_control\pmsm\projects\motor_control_stm32g431_tim`

Encoder SPI Interface

| Signal   | Peripheral | GPIO |
| -------- | ---------- | ---- |
| SPI CS   | SPI2       | PB1  |
| SPI MOSI | SPI2       | PB15 |
| SPI MISO | SPI2       | PB14 |
| SPI CLK  | SPI2       | PB13 |

print USART interface, connected by Debugger.



| Signal    | Peripheral | GPIO |
| --------- | ---------- | ---- |
| USART2 TX | USART2     | PA2  |
| USART2 RX | USART2     | PA3  |

TIM PWM channel



| Signal       | Peripheral | Application  | GPIO |
| ------------ | ---------- | ------------ | ---- |
| PWM Phase UH | TIM1 CH1   | PWM Phase UH | PA8  |
| PWM Phase UL | TIM1 CH1   | PWM Phase UL | PA11 |
| PWM Phase VH | TIM1 CH2   | PWM Phase VH | PC1  |
| PWM Phase VL | TIM1 CH2   | PWM Phase VL | PB0  |
| PWM Phase WH | TIM1 CH3   | PWM Phase WH | PC2  |
| PWM Phase WL | TIM1 CH3   | PWM Phase WL | PB9  |

ADC Resources ???

| Signal | Peripheral | GPIO |
| ------ | ---------- | ---- |
| IB     | ADC1 IN1   | PA0  |
| UC     | ADC1 IN2   | PA1  |
| UB     | ADC1 IN9   | PC3  |
| IA     | ADC2 IN3   | PA6  |
| IC     | ADC2 IN4   | PA7  |
| UA     | ADC2 IN5   | PC4  |
| VDC    | ADC2 IN6   | PC0  |

User interface

| Signal      | Usage       | GPIO |
| ----------- | ----------- | ---- |
| User Button | GPIO Input  | PC13 |
| User LED    | GPIO Output | PA5  |

