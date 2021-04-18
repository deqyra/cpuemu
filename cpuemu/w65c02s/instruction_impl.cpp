#include "instruction_impl.hpp"
#include "cpu.hpp"

namespace emu::w65c02s
{

InstructionImpl::InstructionImpl(CPU* cpu) : _cpu(cpu)
{

}

constexpr uint16_t InstructionImpl::_CycleId(Instruction ins, Byte timing)
{
    return (((uint16_t)((Byte)ins)) << 8) + timing;
}

void InstructionImpl::execute(Instruction ins, Byte timing)
{
    uint16_t cycleId = _CycleId(ins, timing);
    switch (cycleId)
    {
    case _CycleId(Instruction::ADC_ABS,        0x00):
        break;
    case _CycleId(Instruction::ADC_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::ADC_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::ADC_IMM,        0x00):
        break;
    case _CycleId(Instruction::ADC_ZP,         0x00):
        break;
    case _CycleId(Instruction::ADC_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::ADC_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::ADC_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::ADC_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::AND_ABS,        0x00):
        break;
    case _CycleId(Instruction::AND_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::AND_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::AND_IMM,        0x00):
        break;
    case _CycleId(Instruction::AND_ZP,         0x00):
        break;
    case _CycleId(Instruction::AND_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::AND_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::AND_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::AND_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::ASL_ABS,        0x00):
        break;
    case _CycleId(Instruction::ASL_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::ASL_ACC,        0x00):
        break;
    case _CycleId(Instruction::ASL_ZP,         0x00):
        break;
    case _CycleId(Instruction::ASL_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::BBR0,           0x00):
        break;
    case _CycleId(Instruction::BBR1,           0x00):
        break;
    case _CycleId(Instruction::BBR2,           0x00):
        break;
    case _CycleId(Instruction::BBR3,           0x00):
        break;
    case _CycleId(Instruction::BBR4,           0x00):
        break;
    case _CycleId(Instruction::BBR5,           0x00):
        break;
    case _CycleId(Instruction::BBR6,           0x00):
        break;
    case _CycleId(Instruction::BBR7,           0x00):
        break;
    case _CycleId(Instruction::BBS0,           0x00):
        break;
    case _CycleId(Instruction::BBS1,           0x00):
        break;
    case _CycleId(Instruction::BBS2,           0x00):
        break;
    case _CycleId(Instruction::BBS3,           0x00):
        break;
    case _CycleId(Instruction::BBS4,           0x00):
        break;
    case _CycleId(Instruction::BBS5,           0x00):
        break;
    case _CycleId(Instruction::BBS6,           0x00):
        break;
    case _CycleId(Instruction::BBS7,           0x00):
        break;
    case _CycleId(Instruction::BCC,            0x00):
        break;
    case _CycleId(Instruction::BCS,            0x00):
        break;
    case _CycleId(Instruction::BEQ,            0x00):
        break;
    case _CycleId(Instruction::BNE,            0x00):
        break;
    case _CycleId(Instruction::BPL,            0x00):
        break;
    case _CycleId(Instruction::BMI,            0x00):
        break;
    case _CycleId(Instruction::BVC,            0x00):
        break;
    case _CycleId(Instruction::BVS,            0x00):
        break;
    case _CycleId(Instruction::BRA,            0x00):
        break;
    case _CycleId(Instruction::BIT_ABS,        0x00):
        break;
    case _CycleId(Instruction::BIT_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::BIT_IMM,        0x00):
        break;
    case _CycleId(Instruction::BIT_ZP,         0x00):
        break;
    case _CycleId(Instruction::BIT_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::BRK,            0x00):
        break;
    case _CycleId(Instruction::CLC,            0x00):
        break;
    case _CycleId(Instruction::CLD,            0x00):
        break;
    case _CycleId(Instruction::CLI,            0x00):
        break;
    case _CycleId(Instruction::CLV,            0x00):
        break;
    case _CycleId(Instruction::CMP_ABS,        0x00):
        break;
    case _CycleId(Instruction::CMP_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::CMP_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::CMP_IMM,        0x00):
        break;
    case _CycleId(Instruction::CMP_ZP,         0x00):
        break;
    case _CycleId(Instruction::CMP_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::CMP_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::CMP_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::CMP_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::CPX_ABS,        0x00):
        break;
    case _CycleId(Instruction::CPX_IMM,        0x00):
        break;
    case _CycleId(Instruction::CPX_ZP,         0x00):
        break;
    case _CycleId(Instruction::CPY_ABS,        0x00):
        break;
    case _CycleId(Instruction::CPY_IMM,        0x00):
        break;
    case _CycleId(Instruction::CPY_ZP,         0x00):
        break;
    case _CycleId(Instruction::DEC_ABS,        0x00):
        break;
    case _CycleId(Instruction::DEC_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::DEC_ZP,         0x00):
        break;
    case _CycleId(Instruction::DEC_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::DEC_ACC,        0x00):
        break;
    case _CycleId(Instruction::DEX,            0x00):
        break;
    case _CycleId(Instruction::DEY,            0x00):
        break;
    case _CycleId(Instruction::EOR_ABS,        0x00):
        break;
    case _CycleId(Instruction::EOR_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::EOR_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::EOR_IMM,        0x00):
        break;
    case _CycleId(Instruction::EOR_ZP,         0x00):
        break;
    case _CycleId(Instruction::EOR_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::EOR_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::EOR_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::EOR_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::INC_ABS,        0x00):
        break;
    case _CycleId(Instruction::INC_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::INC_ZP,         0x00):
        break;
    case _CycleId(Instruction::INC_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::INC_ACC,        0x00):
        break;
    case _CycleId(Instruction::INX,            0x00):
        break;
    case _CycleId(Instruction::INY,            0x00):
        break;
    case _CycleId(Instruction::JMP_ABS,        0x00):
        break;
    case _CycleId(Instruction::JMP_ABS_IND,    0x00):
        break;
    case _CycleId(Instruction::JMP_ABS_X_IND,  0x00):
        break;
    case _CycleId(Instruction::JSR,            0x00):
        break;
    case _CycleId(Instruction::LDA_ABS,        0x00):
        break;
    case _CycleId(Instruction::LDA_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::LDA_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::LDA_IMM,        0x00):
        break;
    case _CycleId(Instruction::LDA_ZP,         0x00):
        break;
    case _CycleId(Instruction::LDA_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::LDA_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::LDA_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::LDA_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::LDX_ABS,        0x00):
        break;
    case _CycleId(Instruction::LDX_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::LDX_IMM,        0x00):
        break;
    case _CycleId(Instruction::LDX_ZP,         0x00):
        break;
    case _CycleId(Instruction::LDX_ZP_Y,       0x00):
        break;
    case _CycleId(Instruction::LDY_ABS,        0x00):
        break;
    case _CycleId(Instruction::LDY_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::LDY_IMM,        0x00):
        break;
    case _CycleId(Instruction::LDY_ZP,         0x00):
        break;
    case _CycleId(Instruction::LDY_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::LSR_ABS,        0x00):
        break;
    case _CycleId(Instruction::LSR_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::LSR_ACC,        0x00):
        break;
    case _CycleId(Instruction::LSR_ZP,         0x00):
        break;
    case _CycleId(Instruction::LSR_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::NOP,            0x00):
        break;
    case _CycleId(Instruction::ORA_ABS,        0x00):
        break;
    case _CycleId(Instruction::ORA_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::ORA_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::ORA_IMM,        0x00):
        break;
    case _CycleId(Instruction::ORA_ZP,         0x00):
        break;
    case _CycleId(Instruction::ORA_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::ORA_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::ORA_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::ORA_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::PHA,            0x00):
        break;
    case _CycleId(Instruction::PHP,            0x00):
        break;
    case _CycleId(Instruction::PHX,            0x00):
        break;
    case _CycleId(Instruction::PHY,            0x00):
        break;
    case _CycleId(Instruction::PLA,            0x00):
        break;
    case _CycleId(Instruction::PLP,            0x00):
        break;
    case _CycleId(Instruction::PLX,            0x00):
        break;
    case _CycleId(Instruction::PLY,            0x00):
        break;
    case _CycleId(Instruction::RMB0,           0x00):
        break;
    case _CycleId(Instruction::RMB1,           0x00):
        break;
    case _CycleId(Instruction::RMB2,           0x00):
        break;
    case _CycleId(Instruction::RMB3,           0x00):
        break;
    case _CycleId(Instruction::RMB4,           0x00):
        break;
    case _CycleId(Instruction::RMB5,           0x00):
        break;
    case _CycleId(Instruction::RMB6,           0x00):
        break;
    case _CycleId(Instruction::RMB7,           0x00):
        break;
    case _CycleId(Instruction::SMB0,           0x00):
        break;
    case _CycleId(Instruction::SMB1,           0x00):
        break;
    case _CycleId(Instruction::SMB2,           0x00):
        break;
    case _CycleId(Instruction::SMB3,           0x00):
        break;
    case _CycleId(Instruction::SMB4,           0x00):
        break;
    case _CycleId(Instruction::SMB5,           0x00):
        break;
    case _CycleId(Instruction::SMB6,           0x00):
        break;
    case _CycleId(Instruction::SMB7,           0x00):
        break;
    case _CycleId(Instruction::ROL_ABS,        0x00):
        break;
    case _CycleId(Instruction::ROL_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::ROL_IMM,        0x00):
        break;
    case _CycleId(Instruction::ROL_ZP,         0x00):
        break;
    case _CycleId(Instruction::ROL_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::ROR_ABS,        0x00):
        break;
    case _CycleId(Instruction::ROR_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::ROR_IMM,        0x00):
        break;
    case _CycleId(Instruction::ROR_ZP,         0x00):
        break;
    case _CycleId(Instruction::ROR_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::RTI,            0x00):
        break;
    case _CycleId(Instruction::RTS,            0x00):
        break;
    case _CycleId(Instruction::SBC_ABS,        0x00):
        break;
    case _CycleId(Instruction::SBC_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::SBC_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::SBC_IMM,        0x00):
        break;
    case _CycleId(Instruction::SBC_ZP,         0x00):
        break;
    case _CycleId(Instruction::SBC_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::SBC_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::SBC_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::SBC_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::SEC,            0x00):
        break;
    case _CycleId(Instruction::SED,            0x00):
        break;
    case _CycleId(Instruction::SEI,            0x00):
        break;
    case _CycleId(Instruction::STA_ABS,        0x00):
        break;
    case _CycleId(Instruction::STA_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::STA_ABS_Y,      0x00):
        break;
    case _CycleId(Instruction::STA_ZP,         0x00):
        break;
    case _CycleId(Instruction::STA_ZP_IND,     0x00):
        break;
    case _CycleId(Instruction::STA_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::STA_ZP_X_IND,   0x00):
        break;
    case _CycleId(Instruction::STA_ZP_IND_Y,   0x00):
        break;
    case _CycleId(Instruction::STX_ABS,        0x00):
        break;
    case _CycleId(Instruction::STX_ZP,         0x00):
        break;
    case _CycleId(Instruction::STX_ZP_Y,       0x00):
        break;
    case _CycleId(Instruction::STY_ABS,        0x00):
        break;
    case _CycleId(Instruction::STY_ZP,         0x00):
        break;
    case _CycleId(Instruction::STY_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::STZ_ABS,        0x00):
        break;
    case _CycleId(Instruction::STZ_ABS_X,      0x00):
        break;
    case _CycleId(Instruction::STZ_ZP,         0x00):
        break;
    case _CycleId(Instruction::STZ_ZP_X,       0x00):
        break;
    case _CycleId(Instruction::STP,            0x00):
        break;
    case _CycleId(Instruction::TRB_ABS,        0x00):
        break;
    case _CycleId(Instruction::TRB_ZP,         0x00):
        break;
    case _CycleId(Instruction::TSB_ABS,        0x00):
        break;
    case _CycleId(Instruction::TSB_ZP,         0x00):
        break;
    case _CycleId(Instruction::TAX,            0x00):
        break;
    case _CycleId(Instruction::TAY,            0x00):
        break;
    case _CycleId(Instruction::TSX,            0x00):
        break;
    case _CycleId(Instruction::TXA,            0x00):
        break;
    case _CycleId(Instruction::TXS,            0x00):
        break;
    case _CycleId(Instruction::TYA,            0x00):
        break;
    case _CycleId(Instruction::WAI,            0x00):
        break;
    default:
        break;
    }
}

}