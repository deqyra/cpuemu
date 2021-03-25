#ifndef CPUEMU__EMU__MOS6502__CPU_HPP
#define CPUEMU__EMU__MOS6502__CPU_HPP

#include <common/env.hpp>
#include <common/memory.hpp>
#include <common/types.hpp>

#include "instruction.hpp"

namespace emu::mos6502
{

class CPU
{
public:
//////////
// Info //
//////////

    static constexpr Endianness Endianness = Endianness::Little;
    static constexpr unsigned char Bitness = 8;
    static constexpr unsigned char AddressBusSize = 16;
    static constexpr unsigned int MaxMemory = 1 << AddressBusSize;
    using Memory = Memory<MaxMemory>;
    using Word = Word<Endianness>;

    // Memory attached to the CPU
    Memory& mem;

    // Number of cycles completed by the CPU
    uint64_t cycleCount;

////////////////////
/// Constructors ///
////////////////////

    CPU(Memory& mem);

///////////////
// Registers //
///////////////

    // Program counter
    Word PC;

    // Stack pointer
    // Points to memory range [0x0100; 0x01FF]
    Byte S;

    // Accumulator
    Byte A;

    // Register X
    Byte X;

    // Register Y
    Byte Y;

    // Processor status register
    struct StatusRegister
    {
        unsigned char c: 1;  // Carry
        unsigned char z: 1;  // Zero
        unsigned char i: 1;  // Interrupt disable
        unsigned char d: 1;  // Decimal mode
        unsigned char b: 1;  // Break command
        unsigned char u: 1;  // User flag
        unsigned char v: 1;  // Overflow
        unsigned char n: 1;  // Negative
    } P;

//////////////
// Controls //
//////////////
    // Reset the state of the CPU
    void reset();

    // Step through nCycles cycles.
    void step(int64_t nCycles);

    // Fetch the next byte from memory and decode it as an instruction.
    Instruction fetchInstruction();

    // Decode the given instruction and execute it
    void decodeAndExecute(Instruction ins);

///////////////
// Internals //
///////////////
private:
    // Remaining cycles to step through before stopping execution
    int64_t _remCycles;
};

}

#endif//CPUEMU__EMU__MOS6502__CPU_HPP