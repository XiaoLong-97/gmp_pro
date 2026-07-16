# Start a GMP project using TI Sysconfig



## Preparation

For start a GMP project using TI Sysconfig for C28x devices, the following software should be installed first

+ Python3

Website: https://www.python.org/downloads/windows/

In order to run the GMP code generator scripts. In this document, we use Python 3.13 as example.

+ C2000Ware

Website:https://www.ti.com/tool/C2000WARE

In order to provide the library support for the devices. In this document, we use C2000ware 5.03 as example.

+ CCS

Website: https://www.ti.com/tool/CCSTUDIO

In order to create and build the TI C28x devices projects. In this document, we use CCS 12.8.1 as example.

+ Sysconfig

Website: https://www.ti.com/tool/SYSCONFIG

In order to generate TI initialize code. In this document, we use Sysconfig 1.21.2 as example.

## User files

In GMP library, a general User file example is provided in `<GMP>/core/usr`. You may copy this folder to your workspace. Here is a brief introduction.

There are three files for controller implement.

`xplt_ctl_interface.h` provide the interface of the controller. User should implement the specific function to get input.
If you disabled the Controller Nano, the following function would be called.

> `ctl_input_callback()` this function will be called every MainISR, firstly.
>
> `ctl_output_callback()` this function will be called after controller callback.
>
> `ctl_enable_output()` this function should enable controller output.
>
> `ctl_disable_output()` this function should disable controller output.

If you enabled the controller Nano, the following function would be called.

>`ctl_fmif_input_stage_routine()` this function will be called every Main ISR, firstly.
>
>`ctl_fmif_output_stage_routine()` this function will be called after controller callback.
>
>`ctl_fmif_request_stage_routine()` this function will be called every Main ISR, after all the control law callback and output callback.
>
>`ctl_fmif_output_enable()` this function will be called to enable output.
>
>`ctl_fmif_output_disable()` this function will be called to disable output.

`ctl_main.c` will implement the initialization function.

`ctl_main.h` will implement the main control law function.



+ User main and peripheral manager

`cplt.config.h` project config headers.

`user_main.c` implement main init and loop function.

`user_main.h` header of `user_main.c`.

`xplt.peripheral.c` implement the peripheral init function.

`xplt.peripheral.h` define all peripheral declarations.



## GMP Code generator tools preparation

In order to address GMP code, and add them to your workspace, we provide a easy tools for user.

You should copy the folder `<GMP ROOTS>/tools/facilities_generator/gmp_file_generator` to your own project workspace.



## Config Compile environment

Add necessary header paths：

+ Necessary Library Path



+ User files path



+ GMP generated path



Add GMP related files to compiling list.



Add User files to compiling list.



## Enjoy and Start your own controller







