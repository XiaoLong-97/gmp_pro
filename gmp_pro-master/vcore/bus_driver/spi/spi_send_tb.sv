//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称spi_send_tb
module spi_send_tb();

logic spi_clk;//SPI时钟
logic spi_csn;//SPI片选
logic spi_sdi;//SPI数据

//产生50MHz时钟激励
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

//输出一个SPI时序波形，仿真完成
initial begin
  #2000
  $finish;
end

//例化spi_send模块
spi_send spi_send(
  .sys_clk     (sys_clk     ),
  .sys_reset   (sys_reset   ),
  .i_data      (16'haa11    ),
  .i_data_en   (1'b1        ),
  .spi_clk     (spi_clk     ),
  .spi_csn     (spi_csn     ),
  .spi_sdi     (spi_sdi     )); 

endmodule
