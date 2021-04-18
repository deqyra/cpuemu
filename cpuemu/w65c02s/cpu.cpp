#include "cpu.hpp"

#include "instruction.hpp"
#include "instruction_impl.hpp"

namespace emu::w65c02s
{

CPU::CPU(Memory& mem) :
    mem(mem),
    cycleCount(0),
    _instructionImpl(this)
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
    while (nCycles-- < 0) tick();
}

void CPU::tick()
{
    _decodeAndExecute();
}

void CPU::_decodeAndExecute()
{
    _instructionImpl.execute((Instruction)IR, TCU);
}

}