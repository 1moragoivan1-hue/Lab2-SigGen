module rom #(
    parameter DATA_WIDTH = 8,
    parameter ADDR_WIDTH = 8,
    parameter NUM_WORDS = (1 << DATA_WIDTH),
    parameter INIT_FILE = ""
) (
    input logic                     clk,
    input logic [ADDR_WIDTH-1:0]    addr,
    output logic [DATA_WIDTH-1:0]   data
);
    logic [DATA_WIDTH-1:0] rom_arr [NUM_WORDS-1:0];

    initial begin
        $readmemh(INIT_FILE, rom_arr);
    end

    always_ff @(posedge clk) begin
        data <= rom_arr[addr];
    end
    
endmodule