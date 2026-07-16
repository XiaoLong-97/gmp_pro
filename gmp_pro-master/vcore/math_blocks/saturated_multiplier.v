
// This case is from Digital Control of High-Frequency-Switched-Mode Power Converters 

module saturated_multiply
#(
	parameter n,
	parameter p,
	parameter m // m <= n + p
)
(
	input signed [n-1,0] x,
	input signed [n-1,0] y,
	output reg signed [m-1,0] z,
	output reg ov
) 

wire signed [n+p-1:0] zx;

assign zx = x*y;


reg temp;
integer I;

always@(zx) begin
	temp = 1'b0;
	for(I=m; I < n+p-1; I = I + 1) begin
		if((zx[I]^zx[m-1]) = 1'b1)
			temp = 1'b1;
	end

	ov = temp;
end

always@(ov, zx) begin
	case(ov)
		1'b0 : z = zx[m-1:0];
		1'b1 : begin
			if(zx[n+p-1] == 1'b0)
				z = {1'b0, {(m-1){1'b1}}};
			else
				z = {1'b1, {(m-1){1'b0}}};
		end
	endcase
end


endmodule
