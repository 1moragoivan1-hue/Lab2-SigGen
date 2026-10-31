#pragma once

#include "vbuddy.cpp"
#include <concepts>
#include <cstdlib>
class Vbuddy {
public:

    enum class FlagType : int {
        TOGGLE,
        ARMED
    };

    struct PlotRange {
        int min{0};
        int max{255};

        static constexpr PlotRange uint8() { return {0, 1 << 8}; }
        static constexpr PlotRange int8() { return {-(1 << 7), (1 << 7) - 1}; }
        static constexpr PlotRange percentage() { return {0, 100}; }
        static constexpr PlotRange uint16() { return {0, 1 << 16}; }
        static constexpr PlotRange int16() { return {-(1 << 15), (1 << 15) - 1}; }
    };

    Vbuddy(const char* title) {
        if (vbdOpen() != 1) exit(EXIT_FAILURE);
        vbdHeader(title);
    }

    void print_number(std::integral auto num, int digits) {
        for (int i = 1; i <= digits; i++){
            vbdHex(i, (int(num) >> ((i - 1) * 4)) & 0xF);
        }
    }

    void tick(int cycle) { vbdCycle(cycle + 1); }

    bool flag() { return vbdFlag(); }

    void plot(std::integral auto x, PlotRange range = PlotRange::uint8()) { 
        vbdPlot(x, range.min, range.max); 
    }

    unsigned int value() { return vbdValue(); }

    void mode(FlagType flag) { vbdSetMode(static_cast<int>(flag)); }

    ~Vbuddy() {
        vbdClose();
    }
};
