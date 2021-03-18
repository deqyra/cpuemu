#include "cpu.hpp"

namespace emu::mpu6502
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
    P.u = 1;
    P.b = 1;
    P.d = 0;
    P.i = 1;

    PC = (mem[0xFFFD] << 8) + (mem[0xFFFC]);
    S = 0xFF;

    cycleCount = 7;
}

void CPU::step(uint64_t nCycles)
{
    _remCycles = nCycles;
    while (_remCycles > 0)
    {
        Byte ins = fetchInstruction();
    }
}

Byte CPU::fetchInstruction()
{
    Byte ins = mem[PC];
    PC++;
    _remCycles--;
    return ins;
}

void CPU::decodeAndExecute(Byte ins)
{

}

}