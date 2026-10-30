module top(
    input logic         clk,
    input logic         rst,
    input logic         ld,
    input logic [7:0]   incr,
    input logic         en,
    output logic [7:0]  out
);

    logic [7:0] addr;

    counter #(
        .WIDTH(8)
    ) u_counter (
        .clk(clk),
        .en(en),
        .rst(rst),
        .ld(ld),
        .data(incr),
        .count(addr)
    );

    rom #(
        .DATA_WIDTH(8),
        .ADDR_WIDTH(8),
        .INIT_FILE("sinerom.mem")
    ) u_rom (
        .clk(clk),
        .addr(addr),
        .data(out)
    );

endmodule