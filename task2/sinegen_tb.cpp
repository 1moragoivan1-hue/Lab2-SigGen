#include "vbuddy.hpp"
#include "test_bench.hpp"
#include "Vsinegen.h"

int main(int argc, char** argv) {
    CLI::App app("Sine Wave Testbench");

    TestBench::TBConfig config{};
    config.setup(app, __FILE__);
    config.parse_args(argc, argv);
    // init top verilog instance

    TestBench::Simulator<Vsinegen> sim(&config);
    Vbuddy vbuddy("Task 1: Cos Wave");

    sim->clk = 1;
    sim->rst = 0;
    sim->en = 1;
    sim->incr = 1;

    sim.run([&](size_t cycle) {
        sim->offset = vbdValue();
        vbuddy.plot(sim->out1, Vbuddy::PlotRange::uint8());
        vbuddy.plot(sim->out2, Vbuddy::PlotRange::uint8());
    }, &vbuddy);
}