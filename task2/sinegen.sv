module sinegen (
    input  logic       clk,
    input  logic       rst,
    input  logic       en,
    input  logic       ld,
    input  logic [7:0] incr,   // <--- REQUIRED: Added input declaration back
    input  logic [7:0] offset, // Phase difference value
    output logic [7:0] out1,   // Primary sine wave
    output logic [7:0] out2    // Phase-shifted sine wave
);

    logic [7:0] addr1;
    logic [7:0] addr2;

    // Address for second wave = base count + phase offset
    assign addr2 = addr1 + offset;

    // Single shared counter
    counter #(
        .WIDTH(8)
    ) u_counter (
        .clk   (clk),
        .en    (en),
        .rst   (rst),
        .ld    (ld),
        .data  (incr),
        .incr  (incr),
        .count (addr1)
    );

    rom #(
        .DATA_WIDTH(8),
        .ADDR_WIDTH(8),
        .INIT_FILE("../../task2/sinerom.mem")
    ) u_rom1 (
        .clk  (clk),
        .addr (addr1),
        .data (out1)
    );

    rom #(
        .DATA_WIDTH(8),
        .ADDR_WIDTH(8),
        .INIT_FILE("../../task2/sinerom.mem")
    ) u_rom2 (
        .clk  (clk),
        .addr (addr2),
        .data (out2)
    );

endmodule