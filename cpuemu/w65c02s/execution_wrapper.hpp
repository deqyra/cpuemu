#ifndef CPUEMU__W65C02S__EXECUTION_WRAPPER_HPP
#define CPUEMU__W65C02S__EXECUTION_WRAPPER_HPP

#include <vector>

#include <common/types.hpp>
#include <common/memory.hpp>

#include "cpu.hpp"

namespace emu::w65c02s
{

class ExecutionWrapper
{
public:
    ExecutionWrapper();

    // Write a program to internal memory at the provided start address. The CPU
    // will not be reset upon calling this function. The reset vector from main 
    // program start location will be set accordingly.
    void registerProgram(const std::vector<Byte>& program, const uint64_t startAddress);

    // Write data to the memory range at the provided start address.
    void registerMemory(const std::vector<Byte>& memory, const uint64_t startAddress);

    // Have the CPU perform a single cycle of execution
    void cycleStep();

    // Have the CPU perform an entire instruction, return the number of cycles
    // it stepped through.
    // If the CPU is resetting, calling this function will step through the
    // remaining cycles in the reset sequence.
    // If the CPU was requested to reset amidst the execution of the current 
    // instruction, the function will return when the CPU enters the first cycle
    // of its reset sequence.
    uint8_t instructionStep();

private:
    // CPU which will execute the program
    CPU _cpu;

    using Memory = Memory<CPU::MaxMemory>;
    // Memory linked to the CPU
    Memory _mem;

    // Program to execute
    std::vector<Byte> _program;

public:
    // View on the CPU
    const CPU& cpu = _cpu;

    // View on the memory
    const Memory& mem = _mem;
};

}

#endif//CPUEMU__W65C02S__EXECUTION_WRAPPER_HPP
