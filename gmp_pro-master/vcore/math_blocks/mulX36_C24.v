
//(parameter param_index = 0)#

module mulx36_c24(
        input clk,
        input [35:0] state,
        input [26:0] param,
        output[35:0] result
    );

    wire [46:0] result_lsp;

  dsp_macro_0 dsp_lsp(
//    .CLK(clk),
    .A(param),
    .B(state[17:0]),
    .C(27'd0),
    .P(result_lsp)
  );

wire [46:0] result_hsp;

  dsp_macro_0 dsp_hsp(
//    .CLK(clk),
    .A(param),
    .B(state[35:18]),
    .C(result_lsp[46:18]),
    .P(result_hsp)
  );

reg [35:0] result;
//assign result = {result_hsp[46-8:46-8-35]};

always@(posedge clk) begin
  result <= {result_hsp[46-8:46-8-35]};
end



endmodule
