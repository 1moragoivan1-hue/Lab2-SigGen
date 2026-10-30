module counter #(
    parameter WIDTH = 8
) (
    input logic                 clk,
    input logic                 en,
    input logic                 rst,
    input logic                 ld,
    input logic [WIDTH-1:0]     data,
    output logic [WIDTH-1:0]    count    
);

    always_ff @(posedge clk or posedge rst) begin
        if (rst) count <= '0;
        else if (ld) count <= data;
        else if (en) count <= count + 1'b1;
    end
    
endmodule