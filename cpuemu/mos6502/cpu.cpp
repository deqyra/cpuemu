#include "cpu.hpp"

#include "instruction.hpp"
#include "instruction_impl.hpp"

namespace emu::mos6502
{

CPU::CPU(Memory& mem) :
    mem(mem),
    cycleCount(0),
    _remCycles(0)
{
    reset();
}

void CPU::reset()
{
    // Reset by hardware
    P.i = 1;    // Interrupt disable
    P.d = 0;    // Decimal mode
    P.b = 1;    // Break
    P.u = 1;    // User flag

    // To be set by software
    // P.c -- carry
    // P.z -- zero
    // P.v -- overflow
    // P.n -- negative

    PC = (mem[0xFFFD] << 8) + (mem[0xFFFC]);
    S = 0xFF;

    cycleCount = 7;
}

void CPU::step(int64_t nCycles)
{
    _remCycles = nCycles;
    while (_remCycles > 0)
    {
        Instruction ins = fetchInstruction();
        decodeAndExecute(ins);
    }

    cycleCount += nCycles - _remCycles;
}

Instruction CPU::fetchInstruction()
{
    Byte ins = mem[PC];
    PC++;
    _remCycles--;
    return (Instruction) ins;
}

void CPU::decodeAndExecute(Instruction ins)
{
    InstructionMap.at(ins)(*this);
}

}