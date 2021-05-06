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

void ExecutionWrapper::registerMemory(const std::vector<Byte>& memory, const uint64_t startAddress)
{
    _mem[startAddress] = memory;
}

void ExecutionWrapper::cycleStep()
{
    if (_cpu.pins.rnw)              // read cycle
    {
        _cpu.pins.DB = _mem[_cpu.pins.AB];
    }
    else // if (!_cpu.pins.rnw)     // write cycle
    {
        _mem[_cpu.pins.AB] = _cpu.pins.DB;
    }

    _cpu.tick();
}

uint8_t ExecutionWrapper::instructionStep()
{
    uint8_t n = 0;

    // Tick until the next instruction is being fetched
    do
    {
        cycleStep();
        n++;
    }
    while (!_cpu.pins.sync);

    // Return stepped-through cycle countB
    return n;
}

}
