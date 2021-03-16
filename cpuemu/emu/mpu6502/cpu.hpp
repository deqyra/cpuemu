#ifndef CPUEMU__EMU__MPU6502__CPU_HPP
#define CPUEMU__EMU__MPU6502__CPU_HPP

#include <emu/common/memory.hpp>
#include <emu/common/types.hpp>

namespace emu::mpu6502
{

class CPU
{
public:
//////////
// Info //
//////////
    static constexpr Endianness Endianness = Endianness::Little;
    static constexpr unsigned int Bitness = 16;
    static constexpr unsigned int MaxMemory = 1 << Bitness;
    using Memory = Memory<MaxMemory>;



///////////////
// Registers //
///////////////
    // Program counter
    Word PC;

    // Stack pointer
    Byte S;

    // Accumulator
    Byte A;

    // Register X
    Byte X;

    // Register Y
    Byte Y;

    struct StatusRegister
    {
        unsigned int C: 1;  // Carry
        unsigned int Z: 1;  // Zero
        unsigned int I: 1;  // Interrupt disable
        unsigned int D: 1;  // Decimal mode
        unsigned int B: 1;  // Break command
        unsigned int U: 1;  // User flag
        unsigned int V: 1;  // Overflow
        unsigned int N: 1;  // Negative
    } P;

//////////////
// Controls //
//////////////
    // Reset the state of the CPU
    void reset();

    // Fetch and execute instruction from the memory for nCycles.
    void execute(Memory* mem, uint64_t nCycles);
};

}

#endif//CPUEMU__EMU__MPU6502__CPU_HPP