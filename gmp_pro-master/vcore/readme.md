This folder provide FPGA basic support.


# GMP CTL FPGA Support Sub-Library (CTL FPGA SSL)

In this folder would provide the HLS code and Verilog code for controlled objects and controller components.


考虑给gmp配一个parser，这个parser可以根据控制器的实际执行情况进行计算生成。
整个代码分为两个部分
1.计算引擎，全计算（standalone），向量计算器（计算点积），小矩阵加速器（计算分块矩阵），单计算单元（相当于1维的小矩阵或向量计算器），这些实域一套，复数域一套
2.计算表达式，标量等式，矩阵等式（利用引擎拆分成步骤）

本质上相当于做一个verilog的module调用

编码的运行方式分为内存调度（每次读一组或一个指令来计算）和寄存器调度（状态机）

相当于函数原型如下，支持实定点数和复定点数
int proc(参数列表，中间过程列表，输入列表，输出列表，触发?)
申请计算引擎，得到计算引擎的句柄
相当于一个lambda表达式
定义各个变量
里面写具体的计算步骤：xp=a*x+b*u
结束

