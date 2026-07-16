//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称iic_send
module iic_send(
input       sys_clk         ,//系统时钟，频率为200KHz
input       sys_reset       ,//系统复位，高电平有效
input       iic_send_en     ,//用户写使能
input [6:0] iic_device_addr ,//从设备器件地址
input [7:0] iic_send_addr   ,//I用户寄存器地址
input [7:0] iic_send_data   ,//I用户寄存器数据
output      iic_scl         ,//IIC时钟，200KHz
inout       iic_sda        );//IIC数据

parameter  idle              = 8'h01;//空状态
parameter  send_device_state = 8'h02;//发送器件地址状态
parameter  send_addr_state   = 8'h04;//发送用户地址状态
parameter  send_data_state   = 8'h08;//发送用户数据状态
parameter  send_end_state    = 8'h10;//发送结束状态
parameter  send_ack1_state   = 8'h20;//发送器件地址应答状态
parameter  send_ack2_state   = 8'h40;//发送用户地址应答状态
parameter  send_ack3_state   = 8'h80;//发送用户数据应答状态

reg  [7:0]  iic_cstate               ;//当前状态
reg  [7:0]  iic_nstate               ;//下一状态
reg  [3:0]  send_device_cnt          ;//发送器件地址状态计数器
reg  [3:0]  send_addr_cnt            ;//发送用户地址状态计数器
reg  [3:0]  send_data_cnt            ;//发送数据地址状态计数器
reg         iic_ack_en               ;//应答信号使能
wire        iic_ack                  ;//应答信号
reg         sda_reg                  ;//IIC时钟
reg         scl_reg                  ;//IIC数据

//assign iic_ack = iic_sda              ;//实际
assign iic_ack = 1'b0                 ;//仿真

//当前状态跳转
always @(posedge sys_clk)begin
  if(sys_reset)
    iic_cstate <= idle;
  else
    iic_cstate <= iic_nstate;
end

//下一状态跳转
always @(*)begin
  //状态机初始化
  iic_nstate = idle;
  case(iic_cstate)
  idle:begin
    //用户写数据使能，跳转到发送器件地址状态
    if(iic_send_en)
      iic_nstate = send_device_state;
    else
      iic_nstate = idle;    
  end
  send_device_state:begin
    //发送器件地址完成，跳转到器件地址应答状态
    if(send_device_cnt == 'd8)
      iic_nstate = send_ack1_state;
    else
      iic_nstate = send_device_state;
  end
  send_addr_state:begin
    //发送用户地址完成，跳转到用户地址应答状态
    if(send_addr_cnt == 'd8)
      iic_nstate = send_ack2_state;
    else
      iic_nstate = send_addr_state;
  end
  send_data_state:begin
    //发送用户数据完成，跳转到用户数据应答状态
    if(send_data_cnt == 'd8)
      iic_nstate = send_ack3_state;
    else
      iic_nstate = send_data_state;
  end
  send_ack1_state:begin
    if(!iic_ack)//应答响应
      iic_nstate = send_addr_state;
    else
      iic_nstate = send_ack1_state;
  end
  send_ack2_state:begin
    if(!iic_ack)//应答响应
      iic_nstate = send_data_state;
    else
      iic_nstate = send_ack2_state;
  end
   send_ack3_state:begin
    if(!iic_ack)//应答响应
      iic_nstate = send_end_state;
    else
      iic_nstate = send_ack3_state;
  end
  send_end_state:begin
    iic_nstate = idle;//写数据结束
  end
  default:begin
    //防止状态机跑飞，重新回到空状态
    iic_nstate = idle;
  end
  endcase
end

//发送器件地址状态时，计数器计数；其他状态，计数器清零
always @(posedge sys_clk)begin
  if(sys_reset)
    send_device_cnt <= 'd0;
  else if(iic_cstate == send_device_state)
    send_device_cnt <= send_device_cnt + 'd1;
  else
    send_device_cnt <= 'd0;
end

//发送用户地址状态时，计数器计数；其他状态，计数器清零
always @(posedge sys_clk)begin
  if(sys_reset)
    send_addr_cnt <= 'd0;
  else if(iic_cstate == send_addr_state)
    send_addr_cnt <= send_addr_cnt + 'd1;
  else
    send_addr_cnt <= 'd0;
end

//发送用户数据状态时，计数器计数；其他状态，计数器清零
always @(posedge sys_clk)begin
  if(sys_reset)
    send_data_cnt <= 'd0;
  else if(iic_cstate == send_data_state)
    send_data_cnt <= send_data_cnt + 'd1;
  else
    send_data_cnt <= 'd0;
end

always @(posedge sys_clk)begin
  if(sys_reset)
    iic_ack_en <= 'd0;
  else if(iic_cstate == send_device_state)begin
    if(send_device_cnt == 'd8)//器件地址发送完，等待应答
      iic_ack_en <= 'd1;
    else
      iic_ack_en <= 'd0;
  end
  else if(iic_cstate == send_addr_state)begin
    if(send_addr_cnt == 'd8)//用户地址发送完，等待应答
      iic_ack_en <= 'd1;
    else
      iic_ack_en <= 'd0;
  end    
  else if(iic_cstate == send_data_state)begin
    if(send_data_cnt == 'd8)//用户数据发送完，等待应答
      iic_ack_en <= 'd1;
    else
      iic_ack_en <= 'd0;
  end  
  else
    iic_ack_en <= 'd0;
end

//输出IIC数据
always @(posedge sys_clk)begin
  if(sys_reset)
    sda_reg <= 'd1;
  else if(iic_cstate == idle && iic_nstate == send_device_state)
    sda_reg <= 'd0;//IIC开始时序
  else if(iic_cstate == send_device_state)begin
     case(send_device_cnt)//发送器件地址，先发送高位，再发送低位
       'd0:sda_reg <= iic_device_addr[6];
       'd1:sda_reg <= iic_device_addr[5];
       'd2:sda_reg <= iic_device_addr[4];
       'd3:sda_reg <= iic_device_addr[3];
       'd4:sda_reg <= iic_device_addr[2];
       'd5:sda_reg <= iic_device_addr[1];
       'd6:sda_reg <= iic_device_addr[0];
       'd7:sda_reg <= 'd0               ;//0代表写操作
     endcase
  end
  else if(iic_cstate == send_addr_state)begin
     case(send_addr_cnt)//发送用户地址，先发送高位，再发送低位
       'd0:sda_reg <= iic_send_addr[7];
       'd1:sda_reg <= iic_send_addr[6];
       'd2:sda_reg <= iic_send_addr[5];
       'd3:sda_reg <= iic_send_addr[4];
       'd4:sda_reg <= iic_send_addr[3];
       'd5:sda_reg <= iic_send_addr[2];
       'd6:sda_reg <= iic_send_addr[1];
       'd7:sda_reg <= iic_send_addr[0];
     endcase
  end    
  else if(iic_cstate == send_data_state)begin
     case(send_data_cnt)//发送用户数据，先发送高位，再发送低位
       'd0:sda_reg <= iic_send_data[7];
       'd1:sda_reg <= iic_send_data[6];
       'd2:sda_reg <= iic_send_data[5];
       'd3:sda_reg <= iic_send_data[4];
       'd4:sda_reg <= iic_send_data[3];
       'd5:sda_reg <= iic_send_data[2];
       'd6:sda_reg <= iic_send_data[1];
       'd7:sda_reg <= iic_send_data[0];
     endcase
  end
  else if(iic_cstate == send_end_state)
    sda_reg <= 'd1;
end

//输出IIC时钟
always @(*)begin
  scl_reg = 1'b1;
  //发送器件地址时，输出IIC时钟
  if(iic_cstate == send_device_state)
    scl_reg = sys_clk;
  //发送用户地址时，输出IIC时钟
  else if(iic_cstate == send_addr_state)begin
    if(send_addr_cnt == 'd0)
      scl_reg = 1'b1;
    else
      scl_reg = sys_clk;
  end
  //发送用户数据时，输出IIC时钟
  else if(iic_cstate == send_data_state)begin
    if(send_data_cnt == 'd0)
      scl_reg = 1'b1;
    else
      scl_reg = sys_clk;
  end
  else 
    scl_reg = 1'b1;
end

assign iic_scl =  scl_reg;
assign iic_sda = (iic_ack_en)?1'bz:sda_reg;

endmodule
