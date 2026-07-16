//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称uart_baud_rate
module uart_baud_rate(
input        sys_clk           ,//系统时钟，频率为50MHz
input        sys_reset         ,//系统复位，高电平有效
input [31:0] i_uart_bps        ,//波特率设置
output reg   o_uart_clk       );//波特率对应时钟

wire [15:0] bps_max_count;//波特率最大计数值
reg  [15:0] clk_count    ;//波特率计数器

assign bps_max_count =  50_000_000/i_uart_bps;

//计数器等于最大值时，清零计数器
always @(posedge sys_clk)begin
  if(sys_reset)
    clk_count <= 'd0;
  else if(clk_count == bps_max_count)
    clk_count <= 'd0;
  else
    clk_count <= clk_count + 'd1;
end

//波特率对应时钟输出
always @(posedge sys_clk)begin
  if(sys_reset)
    o_uart_clk <= 'd0;
  else if(clk_count == bps_max_count)//满足波特率时钟时，时钟取反
    o_uart_clk <= ~o_uart_clk;
  else
    o_uart_clk <= o_uart_clk;
end

endmodule
