//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称can_send
module can_send(
input            sys_clk         , //系统时钟，频率为5MHz
input            sys_reset       , //系统复位，高电平有效
input      [1:0] i_can_wr_sel    , //用户读写命令，01写，10读
input      [7:0] i_can_wr_addr   , //用户读写地址
input      [7:0] i_can_data      , //用户写数据
input            i_can_data_valid, //用户写数据
output reg[7:0] o_can_addr      , //用户读地址
output reg[7:0] o_can_data      , //用户读数据
output reg      o_can_data_valid, //用户读数据有效
output reg      can_ale         , //CAN接口锁存
output reg      can_cs          , //CAN接口片选
output reg      can_rd          , //CAN接口读使能
output reg      can_wr          , //CAN接口写使能
inout wire [7:0]can_ad          );//CAN接口数据

parameter  can_idle        = 8'h01;//空状态
parameter  can_write_state = 8'h02;//写数据状态
parameter  can_read_state  = 8'h04;//读数据状态
parameter  can_end_state   = 8'h08;//结束状态

reg  [7:0]  can_cstate       ;//当前状态
reg  [7:0]  can_nstate       ;//下一状态
reg  [7:0]  write_cnt        ;//写计数器
reg  [7:0]  read_cnt         ;//读计数器
wire [7:0]  can_ad_rx        ;//读数据变量
reg  [7:0]  can_ad_reg1      ;//写数据变量

//当前状态跳转
always @(posedge sys_clk)begin
  if(sys_reset)
    can_cstate <= can_idle;
  else 
    can_cstate <= can_nstate;
end

//下一状态跳转
always @( * )begin
  can_nstate = can_idle;
  case(can_cstate)
    can_idle:begin
      if(i_can_data_valid)begin
        //写使能，跳转到写状态
        if(i_can_wr_sel == 2'b01)
          can_nstate = can_write_state;
        //读使能，跳转到读状态
        else if(i_can_wr_sel == 2'b10)
          can_nstate = can_read_state;
        else
          can_nstate = can_idle;
      end
      else 
        can_nstate = can_idle;
    end
    can_write_state:begin
      //写数据完成，跳转到结束状态
      if(write_cnt == 'd5)
        can_nstate = can_end_state;
      else
        can_nstate = can_write_state;
    end
    can_read_state:begin
      //读数据完成，跳转到结束状态
      if(read_cnt == 'd5)
        can_nstate = can_end_state;
      else
        can_nstate = can_read_state;
    end
    can_end_state:begin
      //无条件跳转到空状态
      can_nstate = can_idle;
    end
    default:begin
      //无条件跳转到空状态
      can_nstate = can_idle;
    end
  endcase
end

//写数据状态，写计数器计数，其他状态，写计数器清零
always @(posedge sys_clk)begin
  if(sys_reset)
    write_cnt <= 'd0;
  else if(can_cstate == can_write_state)begin
    write_cnt <= write_cnt + 'd1;;
  end
  else 
    write_cnt <= 'd0;
end

//读数据状态，读计数器计数，其他状态，读计数器清零
always @(posedge sys_clk)begin
  if(sys_reset)
    read_cnt <= 'd0;
  else if(can_cstate == can_read_state)
    read_cnt <=  read_cnt + 'd1;
  else
    read_cnt <= 'd0; 
end

//CAN接口输出时序控制
always @(posedge sys_clk)begin
  if(sys_reset)begin
    can_ale     <= 'd0;
    can_cs      <= 'd1;
    can_rd      <= 'd1;
    can_wr      <= 'd1;
    can_ad_reg1 <= 'd0;
  end
  //写数据控制CAN接口为写时序
  else if(can_cstate == can_write_state)begin
    case(write_cnt)
    'd0:begin
      can_ale     <= 'd1;
      can_ad_reg1 <= i_can_wr_addr;
    end
    'd1:begin
      can_ale     <= 'd1;
    end
    'd2:begin
      can_ale     <= 'd0;
      can_cs      <= 'd0;
    end
    'd3:begin
      can_wr      <= 'd0;
      can_ad_reg1 <= i_can_data;
    end
    'd4:begin
      can_wr      <= 'd1;
    end
    'd5:begin
      can_cs      <= 'd1;
    end
    endcase
  end
  //读数据控制CAN接口为读时序
  else if(can_cstate == can_read_state)begin
    case(read_cnt)
    'd0:begin
      can_ale     <= 'd1;
      can_ad_reg1 <= i_can_wr_addr;
    end
    'd1:begin
      can_ale     <= 'd1;
    end
    'd2:begin
      can_ale     <= 'd0;
      can_cs      <= 'd0;
    end
    'd3:begin
      can_rd      <= 'd0;
      can_ad_reg1 <= 'dz;
    end
    'd4:begin
      can_rd      <= 'd1;
      can_ad_reg1 <= 'dz;
    end
    'd5:begin
      can_cs      <= 'd1;
      can_ad_reg1 <= 'd0;
    end
    endcase
  end
  else begin
    can_ale     <= 'd0;
    can_cs      <= 'd1;
    can_rd      <= 'd1;
    can_wr      <= 'd1;
    can_ad_reg1 <= 'd0;
  end
end

assign   can_ad_rx = (read_cnt == 'd4)?8'h5a:8'h00; //仿真使用
//assign   can_ad_rx = (read_cnt == 'd4)?can_ad:8'h00;//实际使用

//写数据时，输出写数据；读数据时，输出高阻态
assign   can_ad   =  (read_cnt == 'd4)? 'dz:can_ad_reg1;

//读数寄存输出
always @(posedge sys_clk)begin
  if(sys_reset)begin
    o_can_addr       <= 'd0;
    o_can_data       <= 'd0;
    o_can_data_valid <= 'd0;
  end
  else if(can_cstate == can_read_state)begin
    if(read_cnt == 'd4)begin
      o_can_addr       <= i_can_wr_addr;
      o_can_data       <= can_ad_rx;
      o_can_data_valid <= 'd1;
    end
    else begin
      o_can_addr       <= o_can_addr;
      o_can_data       <= o_can_data;
      o_can_data_valid <= 'd0;      
    end 
  end
end

endmodule