//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称uart_tb
module uart_tb();
logic       o_uart_clk       ;//用户时钟，波特率为115200
int         sim_count     = 0;//仿真计数器
logic [7:0] i_send_data   = 0;//用户发送数据
logic       i_send_data_en= 0;//用户发送数据有效
logic [7:0] o_receive_data   ;//用户接收数据
logic       o_receive_data_en;//用户接收数据有效
logic       uart_tx          ;//UART发送，1bit
logic       uart_busy        ;//UART发送忙信号

//产生50MHz时钟激励
bit sys_clk  ;
initial begin
  sys_clk = 0;
  forever
  #10 sys_clk = !sys_clk;
end

//产生复位激励
bit  sys_reset;
initial begin
  sys_reset = 1;
  #1000
  sys_reset = 0;
end

//仿真计数器
always @(posedge o_uart_clk)begin
  if(sys_reset)
    sim_count <= 0;
  else
    sim_count <= sim_count + 1'b1;
end

//发送用户数据激励
always @(posedge o_uart_clk)begin
  if(sys_reset)begin
    i_send_data_en <= 'd0;
    i_send_data    <= 'd0;
  end
  else if(sim_count == 10)begin
    i_send_data_en <= 'd1;
    i_send_data    <= {$random}%100;//随机数函数产生随机数
  end
  else begin
    i_send_data_en <= 'd0;
  end
end

//例化uart_baud_rate模块
uart_baud_rate uart_baud_rate(
  .sys_clk            (sys_clk           ),
  .sys_reset          (sys_reset         ),
  .i_uart_bps         ('d115200          ),//波特率配置为115200
  .o_uart_clk         (o_uart_clk        ));

//例化uart_send模块
uart_send uart_send(
  .sys_clk            (o_uart_clk       ),
  .sys_reset          (sys_reset        ),
  .i_send_data        (i_send_data      ),
  .i_send_data_en     (i_send_data_en   ),
  .uart_tx            (uart_tx          ),
  .uart_busy          (uart_busy        ));

//例化uart_receive模块
uart_receive uart_receive(
  .sys_clk            (o_uart_clk       ),
  .sys_reset          (sys_reset        ),
  .uart_rx            (uart_tx          ),
  .o_receive_data     (o_receive_data   ),
  .o_receive_data_en  (o_receive_data_en));

endmodule
