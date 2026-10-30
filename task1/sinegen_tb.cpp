#include "vbuddy.hpp"
#include "test_bench.hpp"
#include "Vsinegen.h"

int main(int argc, char** argv) {
    CLI::App app("Sine Wave Testbench");

    TestBench::TBConfig config{};
    config.setup(app, __FILE__);
    CLI11_PARSE(app, argc, argv);
    Verilated::commandArgs(argc,argv);
    // init top verilog instance

    TestBench::Simulator<Vsinegen> sim(config.vcd_file, config.num_levels, config.trace);
    Vbuddy vbuddy("Task 1: Cos Wave");

    sim->clk = 1;
    sim->rst = 0;
    sim->en = 1;
    sim->incr = 1;
        // run simulation for many clock cycles
    for (size_t cycle = 0; config.should_stop(cycle); cycle++) {
        // dump variables into VCD file and toggle clock 
        sim->ld = (cycle == 0);

        vbdPlot(sim->out, 0, 255);
        sim.tick(cycle);
        if (Verilated::gotFinish()) break;
    }
}