#ifndef CPUEMU__W65C02S__CPU_HPP
#define CPUEMU__W65C02S__CPU_HPP

#include <common/env.hpp>
#include <common/memory.hpp>
#include <common/types.hpp>

#include "instruction.hpp"
#include "instruction_impl.hpp"

namespace emu::w65c02s
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

    // Number of cycles completed by the CPU since last reset
    uint64_t cycleCount;

private:
///////////////
// Internals //
///////////////
    // State of the read/write pin
    bool _rnw;

    // Internal address bus
    Word _AD;

    // Internal state of the sync pin
    bool _sync;

    // Decode and execute the next step of the current instruction
    void _decodeAndExecute();

    // Class which implements the instruction set
    InstructionImpl _instructionImpl;

    friend InstructionImpl;

public:
////////////
// Pinout //
////////////
    // Tells whether the current cycle is read or write
    // rnw stand for "read not write"; read as:
    // if (rnw)  => read, not write => read cycle
    // if (!rnw) => not read, write => write cycle
    const bool& rnw = _rnw;

    // 16 bit address bus
    const Word& AB = _AD;

    // SYNC pin
    const bool& sync = _sync;

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

/////////////
// Control //
/////////////

    // Instruction register
    Byte IR;

    // Timing control unit
    Byte TCU;

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

/////////////
// Special //
/////////////

    // Data bus buffer
    Byte DB;

    // Input data latch
    Byte DL;

////////////////////
/// Constructors ///
////////////////////

    CPU(Memory& mem);

/////////////
// Methods //
/////////////

    // Reset the state of the CPU
    void reset();

    // Have the CPU go through a single cycle
    void tick();

    // Step through nCycles cycles
    void step(int64_t nCycles);
};

}

#endif//CPUEMU__W65C02S__CPU_HPP