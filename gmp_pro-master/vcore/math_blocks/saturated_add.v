
// This case is from Digital Control of High-Frequency-Switched-Mode Power Converters 

module saturated_add
#(
	parameter n,
	parameter p,
	parameter m // m <= max(n, p) + 1
)
(
	input signed [n-1,0] x,
	input signed [n-1,0] y,
	output reg signed [m-1,0] z,
	input wire op,
	output reg ov
) 

function integer max;
	input integer left, right;
	if(left > right)
		max = left;
	else
		max = right;
endfunction

parameter mx = max(n, p) + 1;

wire signed [n:0] xx = {x[n-1], x};
wire signed [p:0] yx = {y[p-1], y};
wire signed [mx-1:0] zx;

% kernel
assign zx = (op==1'b1) ? (xx+yx) : (xx-yx);

reg temp;
integer I;

always @(zx) begin
	temp = 1'b0;
	for(I = m; I < mx-1; I = I+1) begin
		if ((zx[I]^zx[m-1])==1'b1) begin
			temp = 1'b1;
		end
	end

	ov = temp;
end

always@(ov, zx) begin
	case(ov)
		1'b0: z =zx[m-1:0];
		1'b1: begin
			if(zx[mx-1] == 1'b0)
				z = {1'b0, {(m-1){1'b1}}};
			else
				z = {1'b1, {(m-1){1'b0}}};
			end
	endcase
end

endmodule

