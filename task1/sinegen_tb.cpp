#include "vbuddy.hpp"
#include "test_bench.hpp"
#include "Vsinegen.h"

int main(int argc, char** argv) {
    CLI::App app("Sine Wave Testbench");

    TestBench::TBConfig config{};
    config.setup(app, __FILE__);
    config.parse_args(argc, argv);

    TestBench::Simulator<Vsinegen> sim(&config);
    Vbuddy vbuddy("Task 2: Dual Cosine and Sine Wave");

    sim->clk = 1;
    sim->rst = 0;
    sim->en = 1;
    sim->ld = 0;

    sim.run([&](size_t cycle) {
        sim->incr = vbuddy.value();
        vbuddy.plot(sim->out, Vbuddy::PlotRange::uint8());
    }, &vbuddy);
}