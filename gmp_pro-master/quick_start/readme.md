
需要安装的软件

Git

Visual Studio(带Windows平台的包)

Python

MATLAB(最少为2022b版本，如果需要使用SIL仿真功能）

CCS配套的Sysconfig和C2000ware（如果需要调试DSP程序）

安装过程

首先将GMP文件夹移动到没有中文、没有空格、没有其他特殊字符的文件夹中。

运行根目录下的`install_gmp.bat`，运行脚本后将会在用户环境变量中注册环境变量。

如果需要Simulink联合仿真的功能，运行slib文件夹中的`install_gmp_simulink_lib.m`

