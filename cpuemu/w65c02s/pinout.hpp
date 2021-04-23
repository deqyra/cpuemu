#ifndef CPUEMU__W65C02S__PINOUT_HPP
#define CPUEMU__W65C02S__PINOUT_HPP

#include <common/types.hpp>

namespace emu::w65c02s
{

struct Pinout
{
    // Tells whether the current cycle is read or write
    // Stands for "read not write" read as:
    // if (rnw)  => read, not write => read cycle
    // if (!rnw) => not read, write => write cycle
    const bool& rnw;

    // 16 bit address bus
    const Word<Endianness::Little>& AB;

    // SYNC pin, ,pulled up upon instruction fetching
    const bool& sync;

    // Data bus
    Byte& DB;

    // RDY pin, halts the CPU if pulled down
    bool& rdy;

    // RESB pin, pull down for 2 cycles to reset CPU
    bool& resb;
};

}

#endif//CPUEMU__W65C02S__PINOUT_HPP