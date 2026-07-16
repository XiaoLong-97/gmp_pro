// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2022.2 (win64) Build 3671981 Fri Oct 14 05:00:03 MDT 2022
// Date        : Mon Feb  3 11:53:32 2025
// Host        : DESKTOP-UVQF7AQ running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               e:/FPGA/ZU15MINI_MPSOC/source/self/test_application/test_application.gen/sources_1/ip/dsp_macro_0/dsp_macro_0_stub.v
// Design      : dsp_macro_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xczu15eg-ffvb1156-2-i
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "dsp_macro_v1_0_2,Vivado 2022.2" *)
module dsp_macro_0(A, B, C, P)
/* synthesis syn_black_box black_box_pad_pin="A[26:0],B[17:0],C[26:0],P[45:0]" */;
  input [26:0]A;
  input [17:0]B;
  input [26:0]C;
  output [45:0]P;
endmodule
