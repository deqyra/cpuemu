#ifndef CPUEMU__W65C02S__INSTRUCTION_IMPL_HPP
#define CPUEMU__W65C02S__INSTRUCTION_IMPL_HPP

#include <map>
#include <vector>

#include "instruction.hpp"
#include "cycle_op.hpp"

namespace emu::w65c02s
{

class CPU;

class InstructionImpl
{
public:
    InstructionImpl(CPU* cpu);

    // Execute an instruction cycle on the CPU
    void execute(Instruction ins, Byte timing);

private:
    // CPU to execute instructions on
    CPU* _cpu;

    static inline constexpr uint16_t _CycleId(Instruction ins, Byte timing);
};

}

#endif//CPUEMU__W65C02S__INSTRUCTION_IMPL_HPP