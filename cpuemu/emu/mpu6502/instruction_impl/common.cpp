#include "common.hpp"

namespace emu::mpu6502::instruction_impl
{

template<>
Byte fetchByte<AddressingMode::Absolute>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndirect>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithX>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithY>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::AbsoluteIndexedWithXIndirect>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::Accumulator>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::Immediate>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::Implied>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::ProgramCounterRelative>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::Stack>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::ZeroPage>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndirect>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithX>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithY>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndexedWithXIndirect>(CPU& cpu)
{
    
}

template<>
Byte fetchByte<AddressingMode::ZeroPageIndirectIndexedWithY>(CPU& cpu)
{
    
}

}