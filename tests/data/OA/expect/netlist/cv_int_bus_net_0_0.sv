`timescale 1ps/1ps 


module pmos4_standard(
    inout  wire B,
    inout  wire D,
    inout  wire G,
    inout  wire S
);

endmodule


module TEST(
    input  wire VDD,
    input  wire VSS,
    input  wire in,
    output wire out
);

wire [1:0] mid;
wire out2;

pmos4_standard XP2_2 (
    .B( VDD ),
    .D( out2 ),
    .G( in ),
    .S( VSS )
);

pmos4_standard XP2_1 (
    .B( mid[1] ),
    .D( out2 ),
    .G( in ),
    .S( VSS )
);

pmos4_standard XP2_0 (
    .B( mid[0] ),
    .D( out2 ),
    .G( in ),
    .S( VSS )
);

pmos4_standard XP_2 (
    .B( VDD ),
    .D( out ),
    .G( in ),
    .S( VSS )
);

pmos4_standard XP_1 (
    .B( mid[1] ),
    .D( out ),
    .G( in ),
    .S( VSS )
);

pmos4_standard XP_0 (
    .B( mid[0] ),
    .D( out ),
    .G( in ),
    .S( VSS )
);

cds_thru XTH (
    .src( out ),
    .dst( out2 )
);

endmodule
