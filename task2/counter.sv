module counter #(
    parameter WIDTH = 8
) (
    input logic                 clk,
    input logic                 en,
    input logic                 rst,
    input logic                 ld,
    input logic [WIDTH-1:0]     data,
    input logic [WIDTH-1: 0]    incr,
    output logic [WIDTH-1:0]    count    
);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) count <= '0;
        else if (ld) count <= data;
        else if (en) count <= count + incr;
    end
    
endmodule