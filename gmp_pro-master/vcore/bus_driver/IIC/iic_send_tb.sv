//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称iic_send_tb
module iic_send_tb();

logic iic_send_scl;//IIC时钟
wire iic_send_sda;//IIC数据

//产生时钟激励
bit sys_clk;
initial begin
  sys_clk = 0;
  forever
  #10 sys_clk = !sys_clk;
end

//产生复位激励
bit sys_reset;
initial begin
  sys_reset = 1;
  #1000
  sys_reset = 0;
end

//例化iic_send模块
iic_send iic_send(
  .sys_clk         (sys_clk       ),
  .sys_reset       (sys_reset     ),
  .iic_send_en     (1'b1          ),
  .iic_device_addr (7'b1010_111   ),
  .iic_send_addr   (8'h01         ),
  .iic_send_data   (8'haa         ),
  .iic_scl         (iic_send_scl  ) ,
  .iic_sda         (iic_send_sda  ));

endmodule
