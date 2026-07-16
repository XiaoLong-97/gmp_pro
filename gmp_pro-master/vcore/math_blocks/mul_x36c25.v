`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/02/03 16:08:20
// Design Name: 
// Module Name: mul_x36c25
// Project Name: 
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


module mulx36_c25(
        input clk,
        input [35:0] state,
        input [24:0] param,
        output[35:0] result
    );

    wire [43:0] result_lsp;

  dsp_macro_0 dsp_lsp(
//    .CLK(clk),
    .A(param),
    .B(state[17:0]),
    .C(25'd0),
    .P(result_lsp)
  );

wire [43:0] result_hsp;

  dsp_macro_0 dsp_hsp(
//    .CLK(clk),
    .A(param),
    .B(state[35:18]),
    .C(result_lsp[43:18]),
    .P(result_hsp)
  );

reg [35:0] result;
//assign result = {result_hsp[46-8:46-8-35]};

always@(posedge clk) begin
  result <= {result_hsp[43-8:43-8-35]};
end



endmodule
