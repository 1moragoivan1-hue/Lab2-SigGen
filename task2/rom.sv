module rom #(
    parameter DATA_WIDTH = 8,
    parameter ADDR_WIDTH = 8,
    parameter NUM_WORDS = (1 << DATA_WIDTH),
    parameter INIT_FILE = ""
) (
    input logic                     clk,
    input logic [ADDR_WIDTH-1:0]    addr1,
    input logic [ADDR_WIDTH-1:0]    addr2,
    output logic [DATA_WIDTH-1:0]   data1,
    output logic [DATA_WIDTH-1:0]   data2
);
    logic [DATA_WIDTH-1:0] rom_arr [NUM_WORDS-1:0];

    initial begin
        $readmemh(INIT_FILE, rom_arr);
    end

    always_ff @(posedge clk) begin
        data1 <= rom_arr[addr1];
        data2 <= rom_arr[addr2];
    end
    
endmodule