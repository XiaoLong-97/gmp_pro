`timescale 1ns / 1ps

//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: Javnson, Minyi
// 
// Create Date: 2024/11/30 15:15:43
// Design Name: 
// Module Name: top_mul
// Project Name: VCTL
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

module ctl_fp_mul(
	input wire[31:0] ina,
	input wire[31:0] inb,
	output wire[31:0] out,
	output wire ov 
);

wire [61:0] result;

assign result = $signed(ina) * $signed(inb);

wire [61:0] abs_result;

always @(*) begin
	if(result[31] == 1)
		abs_result = ~result + 1;
	else
		abs_result = result;
end

assign ov = &abs_result[31:28];

assign out = {}


endmodule

