#ifndef CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL__COMMON_HPP
#define CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL__COMMON_HPP

#include <common/types.hpp>

#include "../cpu.hpp"
#include "addressing_mode.hpp"

namespace emu::mos6502::instruction_impl
{

template<AddressingMode A>
Byte fetchByte(CPU& cpu) = delete;

template<>
Byte fetchByte<AddressingMode::Absolute>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::AbsoluteIndirect>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithX>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithY>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithXIndirect>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::Accumulator>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::Immediate>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::Implied>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::ProgramCounterRelative>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::Stack>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::ZeroPage>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::ZeroPageIndirect>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithX>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithY>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithXIndirect>(CPU& cpu);

template<>
Byte fetchByte<AddressingMode::ZeroPageIndirectIndexedWithY>(CPU& cpu);

}

#endif//CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL__COMMON_HPP