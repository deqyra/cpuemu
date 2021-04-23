#include "execution_wrapper.hpp"

namespace emu::w65c02s
{

ExecutionWrapper::ExecutionWrapper() :
    _cpu(),
    _mem()
{
    
}

void ExecutionWrapper::registerProgram(const std::vector<Byte>& program, const uint64_t startAddress)
{
    registerMemory(program, startAddress);
    _mem[0xFFFC] = (Byte)(startAddress & 0x00FF);
    _mem[0xFFFD] = (Byte)((startAddress & 0xFF00) >> 8);
}

void ExecutionWrapper::registerMemory(const std::vector<Byte>& program, const uint64_t startAddress)
{
    _mem[startAddress] = program;
}

void ExecutionWrapper::cycleStep()
{
    if (_cpu.pins.rnw) _cpu.pins.DB = _mem[_cpu.pins.AB];   // read cycle
    else _mem[_cpu.pins.AB] = _cpu.pins.DB;                 // write cycle

    _cpu.tick();
}

uint8_t ExecutionWrapper::instructionStep()
{
    cycleStep();
    uint8_t n = 1;

    // Tick until the next instruction is being fetched
    while (!_cpu.pins.sync)
    {
        cycleStep();
        n++;
    }

    // Return stepped-through cycle countB
    return n;
}

}