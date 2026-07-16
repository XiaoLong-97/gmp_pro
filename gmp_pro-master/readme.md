# General Motor Platform (GMP) library manual summary

GMP is a easy-going library which may help you implement a controller easily.

![GMP LOGO](manual/img/GMP_LOGO.png)


GMP contains a set of tools for user, you may find then in specified folders.

| Folders | Summary |
| ------- | :------- |
| core/   | This folder provide a set of basic components for the whole library and user. Such as, workflow and it's scheduling, memory management, and abstract of IO devices and etc.. |
| csp/    | This folder contains all the chip support informations. This predefinitions may help you use the library more easily |
| ctl/    | The controller template library. This folder provides not only basic components but also a whole host of controller and it's workflow agent. |
| cctl/ | Class-based controller template library. This folder provides a set of C++ classes controller, and a simulator. |
| vctl/ | Verilog-based controller template library. This folder provides a example code for controller design. |
| ext/    | The extension module of the library. This folder contains a lot of devices based on the GMP core. These extensions may help you deploy application easily and rapidly. |



## Install GMP Product

If you need to install GMP product you should install the following softwares, in order to make install process smoothly.

git : https://git-scm.com/downloads

python: https://www.python.org/downloads/

Then you may run script `install_gmp.bat`. This script will help you to install and register GMP product.

By this script a environment variable will be created `GMP_PRO_LOCATION` will point to the GMP library root path. In CCS or Visual Studio we strongly recommend you to add source file or include path based on this environment variable.



## Install GMP Simulink SIL Module

If you have a MATLAB which versioin is greater than 2022b, you may install GMP Simulink Module by running a installing m file.

`<GMP ROOT>\slib\install_gmp_simulink_lib.m`



## Start a GMP Project

+ As a GMP user, you may use the full cross-platform service.

### Prepare necessary files

You should copy all the files in `<GMP ROOT>\quick_start\gmp_file_generator` folder to your own project directory.

By runing script `gmp_fac_config_gui.bat` you may config the modules you need.

And Then run script `gmp_fac_generate_src.bat` you may get all the files you need. and a txt file contains include path you should add to your include path. By the way, we recommended you to add the generate code script as the compile preparation step.

For now, you should select a user file template in `<GMP ROOT>/quick_start/usr`. If you will start a SIL project you may copy the folder `ctl_simulation_mtr_model` to your project folder.  If you will start a controller project, you may copy the folder `ctl_nano_framework_model` to your project folder.

Then add this user file into your include path searching options.

### Let GMP code run in your projects

Now invoke GMP, and let GMP framework running.

If your main source file is a C source file, please add the `core/gmp_core.h` just like the following code.

``` C
#include <core/gmp_core.h>
```

If your main source file is a C++ source file, please add the `core/gmp_core.hpp` just like the following code.

``` C++
#include <core/gmp_core.hpp>
```

For now, you may invoke the `gmp_entry()` function in your main function. just like the following code does.

For now, you may invoke the `gmp_entry()` function in your main function. just like the following code does.

``` C++
void main (void)
{
	// Do your preparing code

	// ...

	// Ready to entry the GMP
	gmp_base_entry(); // invoke the GMP library

	// Some other things.
	// But code NEVER reach here.
}
```

> Attention! when `gmp_entry()` is called, the function may not returned. Generally this function should be called after all the initialization code is completed, and 

### Enjoy!

Now you can implement your application based on GMP framework. These code may added in `ctl_main.cpp` and `user_main.cpp`.





+ As a GMP-CTL user, you may disable all the additional functions, just use xplatform (cross platform) CTL module.

We will support this mode in next release version.

## Introduction for GMP Core Module

`gmp_base_` is a general prefix for GMP Core module.

``` C++
// get current system tick
time_gt gmp_base_get_system_tick(void);

// assert function
gmp_base_assert();

// to specify the function isn't impelemted
gmp_base_not_impl();
```



`gmp_hal_` is a general prefix for GMP HAL (Hardware Abstract Layer) module.



`ctl_` is a general prefix for GMP CTL module.

`ctl_init_` is the prefix for initial function of GMP CTL module.

`ctl_step_` is the prefix for controller function of GMP CTL module. This name means discrete controller step to next state.





\
