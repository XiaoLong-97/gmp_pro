`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2025/02/03 16:40:23
// Design Name: 
// Module Name: adder_50
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


module adder_50(
    input clk,
    input [49:0]input1,
    input [49:0]input2,
    output [49:0]out
    );

    wire [49:0]out_temp;

    (*USE_DSP="YES"*)
    assign out_temp = input1 + input2;

    reg [49:0] out;

    always@(posedge clk) begin
        out <= out_temp;
    end

    
endmodule
