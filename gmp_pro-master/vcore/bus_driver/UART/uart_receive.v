//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称uart_receive
module uart_receive(
input            sys_clk            ,//系统时钟，波特率对应时钟
input            sys_reset          ,//系统复位，高电平有效
input            uart_rx            ,//UART接收，1bit
output reg[7:0] o_receive_data     ,//用户接收数据
output reg      o_receive_data_en  );//用户接收数据有效

reg         receive_count_en =0 ;//接收使能
reg   [3:0] receive_count    =0 ;//接收计数器

//接收开始，拉高接收使能；接收结束，拉低接收使能
always @(posedge sys_clk)begin
  if(sys_reset)
    receive_count_en <= 'd0;
  else if(receive_count == 'd8)
    receive_count_en <= 'd0;
  else if(!uart_rx)
    receive_count_en <= 'd1;
end

//接收使能为1时，计数器计数；其他状态，清零计数器
always @(posedge sys_clk)begin
  if(sys_reset)
    receive_count <= 'd0;
  else if(receive_count_en)
    receive_count <= receive_count +'d1;
  else 
    receive_count <= 'd0;
end

//串并转换，将UART串行数据转换为并行数据输出
always @(posedge sys_clk)begin
  if(sys_reset)
    o_receive_data <= 'd0;
  else if(receive_count_en)begin
    case(receive_count)
    'd0:o_receive_data[0] <= uart_rx;//接收第1bit
    'd1:o_receive_data[1] <= uart_rx;//接收第2bit
    'd2:o_receive_data[2] <= uart_rx;//接收第3bit
    'd3:o_receive_data[3] <= uart_rx;//接收第4bit
    'd4:o_receive_data[4] <= uart_rx;//接收第5bit
    'd5:o_receive_data[5] <= uart_rx;//接收第6bit
    'd6:o_receive_data[6] <= uart_rx;//接收第7bit
    'd7:o_receive_data[7] <= uart_rx;//接收第8bit
    endcase
  end
end

//接收数据完成时，输出接收使能信号
always @(posedge sys_clk)begin
  if(sys_reset)
    o_receive_data_en <= 'd0;
  else if(receive_count_en)begin
    if(receive_count == 'd8)
      o_receive_data_en <= 'd1;
    else
      o_receive_data_en <= 'd0;
  end
  else 
    o_receive_data_en <= 'd0;
end

endmodule
