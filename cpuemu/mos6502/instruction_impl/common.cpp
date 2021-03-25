#include "common.hpp"

namespace emu::mos6502::instruction_impl
{

template<>
Byte fetchByte<AddressingMode::Absolute>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndirect>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithX>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithY>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithXIndirect>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::Accumulator>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::Immediate>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::Implied>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::ProgramCounterRelative>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::Stack>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::ZeroPage>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndirect>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithX>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithY>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithXIndirect>(CPU& cpu)
{
    return 0;
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndirectIndexedWithY>(CPU& cpu)
{
    return 0;
}

}