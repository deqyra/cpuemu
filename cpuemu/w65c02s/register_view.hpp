#ifndef CPUEMU__W65C02S__REGISTER_VIEW_HPP
#define CPUEMU__W65C02S__REGISTER_VIEW_HPP

#include <common/types.hpp>

#include "status_register.hpp"

namespace emu::w65c02s
{

struct RegisterView
{
private:
    using Word = Word<Endianness::Little>;

public:
    // Program counter
    const Word& PC;

    // Stack pointer
    // Points to memory range [0x0100; 0x01FF]
    const Byte& S;

    // Accumulator
    const Byte& A;

    // Register X
    const Byte& X;

    // Register Y
    const Byte& Y;

    // Temporary register
    const Byte& TMP;

    // Instruction register
    const Byte& IR;

    // Timing control unit
    const Byte& TCU;

    // Processor status register
    const StatusRegister& P;
};

}

#endif//CPUEMU__W65C02S__REGISTER_VIEW_HPP