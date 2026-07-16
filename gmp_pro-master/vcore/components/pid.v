// TODO to be implemented


// This case is from Digital Control of High-Frequency-Switched-Mode Power Converters 


module pid(
input clk,
input signed [2:0] kp,
input signed [3:0] ki,
input signed [2:0] kd,
input signed [8:0] e,
output signed [10:0] u
)

reg signed [8:0] e1;
wire signed [5:0] up;

wire signed [13:0] ui;
reg signed [13:0] ui1;
wire signed [6:0] wi;

wire signed [6:0] ud;
wire signed [8:0] wd;

wire signed [16:0] upd;
wire signed [13:0] upid;
wire signed [10:0] ux;

// combinational part

saturated_multiply kp_mult(e,kp,up, , );
defparam kp_mult.n = 9, kp_mult.p = 3, kp_mult.m = 6;

saturated_multiply ki_mult(e,kp,up, , );
defparam ki_mult.n = 9, ki_mult.p = 4, ki_mult.m = 7;

saturated_add ki_add(ui1,wi,ui, , 1'b1);
defparam ki_add.n = 14, ki_add.p = 7, ki_add.m = 14;

saturated_add kd_sub(e,e1,wd, ,1'b0);
defparam kd_sub.n = 9, kd_sub.p = 9, kd_sub.m = 9;

saturated_multiply kd_mult(wd,kp,ud, , );
defparam kd_mult.n = 9, kd_mult.p = 3, kd_mult.m = 7;

saturated_add upd_add({up, 6'b0},{ud, 9'b0},upd, 1'b1);
defparam ki_add.n = 12, ki_add.p = 16, ki_add.m = 17;

saturated_add upd_add(upd,ui,upid, 1'b1);
defparam ki_add.n = 17, ki_add.p = 14, ki_add.m = 14;

assign ux = upid[13:3];
assign u = (ux[10] == 1'b1) ? 11'b0:ux;

// sequential part

always @(posedge clk) begin
	ui1 < ui;
	e1 <= e;
end

endmodule

X