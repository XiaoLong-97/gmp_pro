//时间尺度预编译指令
`timescale 1ns / 1ps

//模块名称spi_send
module spi_send(
input       sys_clk          , //系统时钟，频率为50MHz
input       sys_reset        , //系统复位，高电平有效
input[15:0] i_data           , //发送并行数据
input       i_data_en        , //发送并行数据使能
output      spi_clk          , //SPI串行时钟，50MHz
output      spi_csn          , //SPI片选，低电平有效
output      spi_sdi          );//SPI串行数据

parameter    spi_idle       = 4'h1;//空状态
parameter    spi_send_state = 4'h2;//发送数据状态
parameter    spi_send_gap   = 4'h4;//发送间隔状态
parameter    spi_send_end   = 4'h8;//发送结束状态

reg     [3:0] spi_cstate           ;//当前状态
reg     [3:0] spi_nstate           ;//下一状态
reg     [4:0] send_cnt             ;//发送数据状态计数器
reg     [31:0]send_gap_cnt         ;//发送间隔状态计数器
reg     [15:0]data_reg1            ;//发送数据
reg           dac_clk_reg1         ;//SPI时钟
reg           dac_csn_reg1         ;//SPI片选
reg           dac_sdi_reg1         ;//SPI数据

//当前状态跳转
always @(posedge sys_clk)begin
  if(sys_reset)
    spi_cstate <= spi_idle;
  else
    spi_cstate <= spi_nstate;
end

//下一状态跳转
always @(*) begin
  spi_nstate = spi_idle;//状态机初始化
  case(spi_cstate)
    spi_idle:begin
      if(i_data_en == 1'b1)//发送数据开始
        spi_nstate = spi_send_state;
      else
        spi_nstate = spi_idle; 
    end
    spi_send_state:begin
      if(send_cnt == 'd15)//发送数据结束
        spi_nstate = spi_send_gap;
      else
        spi_nstate = spi_send_state;   
    end
    spi_send_gap:begin
      if(send_gap_cnt == 'd100)//两个数据发送间隔控制
        spi_nstate = spi_send_end;
      else
        spi_nstate = spi_send_gap;
    end
    spi_send_end:begin
      spi_nstate = spi_idle;
    end
    default:begin
      spi_nstate = spi_idle;//防止状态机跑飞
    end
  endcase
end

//发送数据状态，计数器计数；其他状态，计数器清零
always @(posedge sys_clk)begin
  if(sys_reset)
    send_cnt <= 'd0;
  else if(spi_cstate == spi_send_state)
    send_cnt <= send_cnt + 'd1;
  else
    send_cnt <= 'd0;
end

//发送间隔状态，计数器计数；其他状态。计数器清零
always @(posedge sys_clk)begin
  if(sys_reset)
    send_gap_cnt <= 'd0;
  else if(spi_cstate == spi_send_gap)
    send_gap_cnt <= send_gap_cnt + 'd1;
  else
    send_gap_cnt <= 'd0;
end

//寄存发送数据
always @(posedge sys_clk)begin
  if(sys_reset)
    data_reg1 <= 'd0;
  else if(spi_cstate == spi_idle)begin
    data_reg1 <= i_data;
  end
end

//SPI串行时钟输出
always @( * )begin
  if(dac_csn_reg1)
  //片选为高，SPI无时钟输出
    dac_clk_reg1 = 1'b0;
  else
  //片选为低，SPI时钟输出
    dac_clk_reg1 = ~sys_clk;
end

//SPI片选信号输出
always @(posedge sys_clk)begin
  if(sys_reset)
    dac_csn_reg1 <= 'd1;
  else if(spi_cstate == spi_send_state)//发送数据时，拉低片选
    dac_csn_reg1 <= 'd0;
  else
    dac_csn_reg1 <= 'd1;
end

//SPI串行数据输出
always @(posedge sys_clk)begin
  if(sys_reset)
    dac_sdi_reg1 <= 'd0;
  //发送数据状态，发送数据，先发并行数据高位，再发并行数据低位
  else if(spi_cstate == spi_send_state)begin
    case(send_cnt)
      'd0 :dac_sdi_reg1 <= data_reg1[15];//MSB(15bit)
      'd1 :dac_sdi_reg1 <= data_reg1[14];//MSB(14bit)
      'd2 :dac_sdi_reg1 <= data_reg1[13];//MSB(13bit)
      'd3 :dac_sdi_reg1 <= data_reg1[12];//MSB(12bit)
      'd4 :dac_sdi_reg1 <= data_reg1[11];//MSB(11bit)
      'd5 :dac_sdi_reg1 <= data_reg1[10];//MSB(10bit)
      'd6 :dac_sdi_reg1 <= data_reg1[09];//MSB(09bit)
      'd7 :dac_sdi_reg1 <= data_reg1[08];//MSB(08bit)
      'd8 :dac_sdi_reg1 <= data_reg1[07];//MSB(07bit)
      'd9 :dac_sdi_reg1 <= data_reg1[06];//MSB(06bit)
      'd10:dac_sdi_reg1 <= data_reg1[05];//MSB(05bit)
      'd11:dac_sdi_reg1 <= data_reg1[04];//MSB(04bit)
      'd12:dac_sdi_reg1 <= data_reg1[03];//MSB(03bit)
      'd13:dac_sdi_reg1 <= data_reg1[02];//MSB(02bit)
      'd14:dac_sdi_reg1 <= data_reg1[01];//MSB(01bit)
      'd15:dac_sdi_reg1 <= data_reg1[00];//LSB(00bit)
      default:dac_sdi_reg1 <= 'd0;
    endcase
  end
  else dac_sdi_reg1 <= 'd0;
end

assign spi_clk = dac_clk_reg1;
assign spi_csn = dac_csn_reg1;
assign spi_sdi = dac_sdi_reg1;

endmodule
