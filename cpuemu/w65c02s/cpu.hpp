#ifndef CPUEMU__W65C02S__CPU_HPP
#define CPUEMU__W65C02S__CPU_HPP

#include <common/env.hpp>
#include <common/memory.hpp>
#include <common/types.hpp>

#include "instruction.hpp"

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
    using Word = Word<Endianness>;

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
    };

private:
///////////////////////////
// Registers / Internals //
///////////////////////////
    // Program counter
    Word _PC;

    // Stack pointer
    // Points to memory range [0x0100; 0x01FF]
    Byte _S;

    // Accumulator
    Byte _A;

    // Register X
    Byte _X;

    // Register Y
    Byte _Y;

    // Temporary register
    Byte _TMP;

    // Internal address bus
    Word _AD;

    // Internal address bus
    Byte _DB;

    // State of the read/write pin
    bool _rnw;

    // Internal state of the sync pin
    bool _sync;

    // Whether to continue execution
    bool _rdy;

    // Pull down at least two cycles to initiate reset sequence
    bool _resb;

    // Tells whether the RESB pin was already pulled down last cycle
    bool __lastCycleWasReset;

    // Tells which cycle of the reset sequence the processor is currently going through
    uint8_t __currentResetCycle;

    // Tells whether the next cycle is an op-code fetch
    bool __syncNext;

/////////////
// Control //
/////////////
    // Instruction register
    Byte _IR;

    // Timing control unit
    Byte _TCU;

    // Processor status register
    StatusRegister _P;

    // Setup the sync flag for next cycle
    void _updateSync();

    // Decode and execute the next step of the current instruction
    void _decodeAndExecute();

    // Return a code to identify "which" cycle to perform in order to carry out 
    // the given instruction at the given timing
    static inline uint16_t _CycleId(Instruction ins, Byte timing);

    // Compile-time-enforced version of the _CycleId(ins, timing) function
    template<Instruction Ins, Byte Timing>
    static inline constexpr uint16_t _CycleId()
    {
        constexpr uint16_t n = (static_cast<uint16_t>(Ins) << 8) + Timing;
        return n;
    }

    // Put PC contents in address bus and set sync up
    void _fetchInstruction();

    // Execute the next reset cycle
    void _continueReset();

    // Implementation of the 7-cycle reset sequence
    void _resetSequence_cycle1();
    void _resetSequence_cycle2();
    void _resetSequence_cycle3();
    void _resetSequence_cycle4();
    void _resetSequence_cycle5();
    void _resetSequence_cycle6();
    void _resetSequence_cycle7();

public:
////////////
// Pinout //
////////////
    // Tells whether the current cycle is read or write
    // Stands for "read not write" read as:
    // if (rnw)  => read, not write => read cycle
    // if (!rnw) => not read, write => write cycle
    const bool& rnw = _rnw;

    // 16 bit address bus
    const Word& AB = _AD;

    // SYNC pin
    const bool& sync = _sync;

    // Data bus
    Byte& DB = _DB;

    // RDY pin
    bool& rdy = _rdy;

    // RESB pin
    bool& resb = _resb;

////////////////////
/// Constructors ///
////////////////////
    CPU();

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