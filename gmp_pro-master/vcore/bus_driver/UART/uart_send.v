//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称uart_send
module uart_send(
input       sys_clk          ,//系统时钟，波特率对应时钟
input       sys_reset        ,//系统复位，高电平有效
input [7:0] i_send_data      ,//用户发送数据
input       i_send_data_en   ,//用户发送数据有效
output reg  uart_tx          ,//UART发送，1bit
output reg  uart_busy       );//UART发送忙，1忙，0闲

reg   [7:0] data_reg1       =0;//发送并行数据
reg         send_enable     =0;//发送使能
reg   [3:0] send_enable_cnt =0;//发送计数器

//寄存发送数据
always @(posedge sys_clk)begin
  if(sys_reset)
    data_reg1 <= 'd0;
  else if(i_send_data_en)
    data_reg1 <= i_send_data;
end

//发送开始，拉高发送使能；发送结束，拉低发送使能
always @(posedge sys_clk)begin
  if(sys_reset)
    send_enable <= 'd0;
  else if(send_enable_cnt == 'd9)
    send_enable <= 'd0;
  else if(i_send_data_en)
    send_enable <= 'd1;
end

//发送使能为1，计数器计数；其他状态，清零计数器
always @(posedge sys_clk)begin
  if(sys_reset)
    send_enable_cnt <= 'd0;
  else if(send_enable)
    send_enable_cnt <= send_enable_cnt + 'd1;
  else 
    send_enable_cnt <= 'd0;
end

//并串转换，将用户并行数据转换为串行数据输出
always @(posedge sys_clk)begin
  if(sys_reset)
    uart_tx <= 'd1;
  else if(send_enable)begin
    case(send_enable_cnt)
          'd0:uart_tx <= 'd0         ;//发送开始
          'd1:uart_tx <= data_reg1[0];//发送第1bit
          'd2:uart_tx <= data_reg1[1];//发送第2bit
          'd3:uart_tx <= data_reg1[2];//发送第3bit
          'd4:uart_tx <= data_reg1[3];//发送第4bit
          'd5:uart_tx <= data_reg1[4];//发送第5bit
          'd6:uart_tx <= data_reg1[5];//发送第6bit
          'd7:uart_tx <= data_reg1[6];//发送第7bit
          'd8:uart_tx <= data_reg1[7];//发送第8bit
          'd9:uart_tx <= 'd1         ;//发送结束
      default:uart_tx <= 'd1;
    endcase
  end
end

//发数据时，处于忙状态；不发送数据时，处于闲状态
always @( * )begin
  if(sys_reset)
    uart_busy = 'd0;
  else if(i_send_data_en == 1'b1)
    uart_busy = 'd1;
  else if(send_enable == 1'b1)
    uart_busy = 'd1;
  else if(send_enable_cnt == 'd10)
    uart_busy = 'd1;
  else
    uart_busy = 'd0;
end

endmodule
