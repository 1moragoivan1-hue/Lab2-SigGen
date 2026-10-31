#pragma once

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.hpp"
#include "CLI/CLI.hpp"
#include <cstdlib>
#include <concepts>

namespace TestBench{
    struct TBConfig {
        int num_cycles{300};
        int num_levels{99};
        std::string vcd_file{""};
        bool trace{false};
        int digits = 5;
        bool unbounded = false;
        CLI::App* cli_app;
        

        void setup(CLI::App &app, const std::string &source_file) {
            cli_app = &app;
            app.option_defaults()->always_capture_default();

            vcd_file = std::filesystem::path(source_file).stem().string() + ".vcd";
            app.add_option("-c,--cycles", num_cycles, "Number of simulation cycles");
            app.add_option("-l,--lvl", num_levels, "Number of levels");
            app.add_option("--vcd", vcd_file, "VCD output filename");
            app.add_option("--digits,-d", digits, "Number of digits on screen");
            app.add_flag("-t,--trace", trace, "Enable signal tracing");
            app.add_flag("-u,--unbounded", unbounded, "Run loop forever (usually on Vbuddy)");
        }

        void parse_args(int argc, char** argv) {
            try {
                cli_app->parse(argc, argv);
            } catch (const CLI::ParseError &e) {
                std::exit(cli_app->exit(e));
            }
            Verilated::commandArgs(argc, argv);
        }
    };

    template <typename Module>
    class Simulator {
    public:
        Simulator(TBConfig* config) : config(config) {
            Verilated::traceEverOn(config->trace);
            top = std::make_unique<Module>();

            if (config->trace) {
                tfp = std::make_unique<VerilatedVcdC>();
                top->trace(tfp.get(), config->num_levels);
                tfp->open(config->vcd_file.c_str());
            }
        }

        ~Simulator() {
            if (tfp) {
                tfp->close();
            }
        }

        Module* operator->() { return top.get(); }
        VerilatedVcdC* get() const { return tfp.get(); }

        void run(std::invocable<std::size_t> auto logic, Vbuddy* vbd = nullptr) {
            for (size_t cycle = 0; should_continue(cycle); cycle++) {
                // task specific logic 
                logic(cycle);

                tick(cycle);
                if (vbd) vbd->tick(cycle);
                if (Verilated::gotFinish() || (vbd && vbdGetkey() == 'q')) break;
            }
        }

        void tick(size_t cycle) {
            for (int i=0; i<2; i++) {
                if (tfp) tfp->dump(2*cycle + i);     
                top->clk = !top->clk;
                top->eval();
            }
        }
    
    private:
        std::unique_ptr<VerilatedVcdC> tfp = nullptr;
        std::unique_ptr<Module> top = nullptr;
        TBConfig* config;

        bool should_continue(int cycle) {
            return config->unbounded ? true : cycle < config->num_cycles;
        }

    };
}

