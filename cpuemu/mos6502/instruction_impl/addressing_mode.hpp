#ifndef CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL__ADDRESSING_MODE_HPP
#define CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL__ADDRESSING_MODE_HPP

#include "../cpu.hpp"

namespace emu::mos6502::instruction_impl
{

enum class AddressingMode
{
    Absolute,
    AbsoluteIndirect,
    AbsoluteIndexedWithX,
    AbsoluteIndexedWithY,
    AbsoluteIndexedWithXIndirect,
    Accumulator,
    Immediate,
    Implied,
    ProgramCounterRelative,
    Stack,
    ZeroPage,
    ZeroPageIndirect,
    ZeroPageIndexedWithX,
    ZeroPageIndexedWithY,
    ZeroPageIndexedWithXIndirect,
    ZeroPageIndirectIndexedWithY
};

}

#endif//CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL__ADDRESSING_MODE_HPP