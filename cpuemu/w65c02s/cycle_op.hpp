#ifndef CPUEMU__W65C02S__CYCLE_OP_HPP
#define CPUEMU__W65C02S__CYCLE_OP_HPP

namespace emu::w65c02s
{

enum class CycleOp
{
    FetchInstruction,
    AddWithCarry,
    SetFlagsForDecimal,
    TemporaryToAccumulator,
};

}

#endif//CPUEMU__W65C02S__CYCLE_OP_HPP