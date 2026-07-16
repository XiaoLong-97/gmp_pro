`timescale 1ns / 1ps

// This file provide a double edge detector, it will help you transfer a async pulse to 
// a sync index.


module edge_detector
#(
	parameter qualification_width = 4,
	parameter qualification_pos = 4'b1111,
	parameter qualification_neg = 4'b1111,
	parameter default_record = 0
)
(
	input wire clk,
	input wire nrst,

	input wire channel,
	output reg pos_edge,
	output reg neg_edge
)

	reg [qualification_width : 0] record;

	// generate records
	always @(posedge clk or negedge nrst) begin
		if(!nrst) begin
			record <= default_record;
		end
		else begin
			record <= {record[qualification_width - 2: 0], channel};
		end

	end

	always @(*) begin 
		if(!nrst) begin
			pos_edge <= 0;
		end
		else begin
			if(record == qualification_pos) begin
				pos_edge <= 1;
			end
			else begin
				pos_edge <= 0;
			end
		end
	end

	always @(*) begin 
		if(!nrst) begin
			neg_edge <= 0;
		end
		else begin
			if(record == qualification_nrg) begin
				neg_edge <= 1;
			end
			else begin
				neg_edge <= 0;
			end
		end
	end

endmodule



