#ifndef CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL_HPP
#define CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL_HPP

#include <map>

#include "cpu.hpp"
#include "instruction.hpp"

namespace emu::mos6502
{

using InstructionImplFun = void(CPU&);

namespace instruction_impl
{
    void ADC_ABS_impl(CPU& cpu);
    void ADC_ABS_X_impl(CPU& cpu);
    void ADC_ABS_Y_impl(CPU& cpu);
    void ADC_IMM_impl(CPU& cpu);
    void ADC_ZP_impl(CPU& cpu);
    void ADC_ZP_IND_impl(CPU& cpu);
    void ADC_ZP_X_impl(CPU& cpu);
    void ADC_ZP_X_IND_impl(CPU& cpu);
    void ADC_ZP_IND_Y_impl(CPU& cpu);
    void AND_ABS_impl(CPU& cpu);
    void AND_ABS_X_impl(CPU& cpu);
    void AND_ABS_Y_impl(CPU& cpu);
    void AND_IMM_impl(CPU& cpu);
    void AND_ZP_impl(CPU& cpu);
    void AND_ZP_IND_impl(CPU& cpu);
    void AND_ZP_X_impl(CPU& cpu);
    void AND_ZP_X_IND_impl(CPU& cpu);
    void AND_ZP_IND_Y_impl(CPU& cpu);
    void ASL_ABS_impl(CPU& cpu);
    void ASL_ABS_X_impl(CPU& cpu);
    void ASL_ACC_impl(CPU& cpu);
    void ASL_ZP_impl(CPU& cpu);
    void ASL_ZP_X_impl(CPU& cpu);
    void BBR0_impl(CPU& cpu);
    void BBR1_impl(CPU& cpu);
    void BBR2_impl(CPU& cpu);
    void BBR3_impl(CPU& cpu);
    void BBR4_impl(CPU& cpu);
    void BBR5_impl(CPU& cpu);
    void BBR6_impl(CPU& cpu);
    void BBR7_impl(CPU& cpu);
    void BBS0_impl(CPU& cpu);
    void BBS1_impl(CPU& cpu);
    void BBS2_impl(CPU& cpu);
    void BBS3_impl(CPU& cpu);
    void BBS4_impl(CPU& cpu);
    void BBS5_impl(CPU& cpu);
    void BBS6_impl(CPU& cpu);
    void BBS7_impl(CPU& cpu);
    void BCC_impl(CPU& cpu);
    void BCS_impl(CPU& cpu);
    void BEQ_impl(CPU& cpu);
    void BNE_impl(CPU& cpu);
    void BPL_impl(CPU& cpu);
    void BMI_impl(CPU& cpu);
    void BVC_impl(CPU& cpu);
    void BVS_impl(CPU& cpu);
    void BRA_impl(CPU& cpu);
    void BIT_ABS_impl(CPU& cpu);
    void BIT_ABS_X_impl(CPU& cpu);
    void BIT_IMM_impl(CPU& cpu);
    void BIT_ZP_impl(CPU& cpu);
    void BIT_ZP_X_impl(CPU& cpu);
    void BRK_impl(CPU& cpu);
    void CLC_impl(CPU& cpu);
    void CLD_impl(CPU& cpu);
    void CLI_impl(CPU& cpu);
    void CLV_impl(CPU& cpu);
    void CMP_ABS_impl(CPU& cpu);
    void CMP_ABS_X_impl(CPU& cpu);
    void CMP_ABS_Y_impl(CPU& cpu);
    void CMP_IMM_impl(CPU& cpu);
    void CMP_ZP_impl(CPU& cpu);
    void CMP_ZP_IND_impl(CPU& cpu);
    void CMP_ZP_X_impl(CPU& cpu);
    void CMP_ZP_X_IND_impl(CPU& cpu);
    void CMP_ZP_IND_Y_impl(CPU& cpu);
    void CPX_ABS_impl(CPU& cpu);
    void CPX_IMM_impl(CPU& cpu);
    void CPX_ZP_impl(CPU& cpu);
    void CPY_ABS_impl(CPU& cpu);
    void CPY_IMM_impl(CPU& cpu);
    void CPY_ZP_impl(CPU& cpu);
    void DEC_ABS_impl(CPU& cpu);
    void DEC_ABS_X_impl(CPU& cpu);
    void DEC_ZP_impl(CPU& cpu);
    void DEC_ZP_X_impl(CPU& cpu);
    void DEC_ACC_impl(CPU& cpu);
    void DEX_impl(CPU& cpu);
    void DEY_impl(CPU& cpu);
    void EOR_ABS_impl(CPU& cpu);
    void EOR_ABS_X_impl(CPU& cpu);
    void EOR_ABS_Y_impl(CPU& cpu);
    void EOR_IMM_impl(CPU& cpu);
    void EOR_ZP_impl(CPU& cpu);
    void EOR_ZP_IND_impl(CPU& cpu);
    void EOR_ZP_X_impl(CPU& cpu);
    void EOR_ZP_X_IND_impl(CPU& cpu);
    void EOR_ZP_IND_Y_impl(CPU& cpu);
    void INC_ABS_impl(CPU& cpu);
    void INC_ABS_X_impl(CPU& cpu);
    void INC_ZP_impl(CPU& cpu);
    void INC_ZP_X_impl(CPU& cpu);
    void INC_ACC_impl(CPU& cpu);
    void INX_impl(CPU& cpu);
    void INY_impl(CPU& cpu);
    void JMP_ABS_impl(CPU& cpu);
    void JMP_ABS_IND_impl(CPU& cpu);
    void JMP_ABS_X_IND_impl(CPU& cpu);
    void JSR_impl(CPU& cpu);
    void LDA_ABS_impl(CPU& cpu);
    void LDA_ABS_X_impl(CPU& cpu);
    void LDA_ABS_Y_impl(CPU& cpu);
    void LDA_IMM_impl(CPU& cpu);
    void LDA_ZP_impl(CPU& cpu);
    void LDA_ZP_IND_impl(CPU& cpu);
    void LDA_ZP_X_impl(CPU& cpu);
    void LDA_ZP_X_IND_impl(CPU& cpu);
    void LDA_ZP_IND_Y_impl(CPU& cpu);
    void LDX_ABS_impl(CPU& cpu);
    void LDX_ABS_Y_impl(CPU& cpu);
    void LDX_IMM_impl(CPU& cpu);
    void LDX_ZP_impl(CPU& cpu);
    void LDX_ZP_Y_impl(CPU& cpu);
    void LDY_ABS_impl(CPU& cpu);
    void LDY_ABS_X_impl(CPU& cpu);
    void LDY_IMM_impl(CPU& cpu);
    void LDY_ZP_impl(CPU& cpu);
    void LDY_ZP_X_impl(CPU& cpu);
    void LSR_ABS_impl(CPU& cpu);
    void LSR_ABS_X_impl(CPU& cpu);
    void LSR_ACC_impl(CPU& cpu);
    void LSR_ZP_impl(CPU& cpu);
    void LSR_ZP_X_impl(CPU& cpu);
    void NOP_impl(CPU& cpu);
    void ORA_ABS_impl(CPU& cpu);
    void ORA_ABS_X_impl(CPU& cpu);
    void ORA_ABS_Y_impl(CPU& cpu);
    void ORA_IMM_impl(CPU& cpu);
    void ORA_ZP_impl(CPU& cpu);
    void ORA_ZP_IND_impl(CPU& cpu);
    void ORA_ZP_X_impl(CPU& cpu);
    void ORA_ZP_X_IND_impl(CPU& cpu);
    void ORA_ZP_IND_Y_impl(CPU& cpu);
    void PHA_impl(CPU& cpu);
    void PHP_impl(CPU& cpu);
    void PHX_impl(CPU& cpu);
    void PHY_impl(CPU& cpu);
    void PLA_impl(CPU& cpu);
    void PLP_impl(CPU& cpu);
    void PLX_impl(CPU& cpu);
    void PLY_impl(CPU& cpu);
    void RMB0_impl(CPU& cpu);
    void RMB1_impl(CPU& cpu);
    void RMB2_impl(CPU& cpu);
    void RMB3_impl(CPU& cpu);
    void RMB4_impl(CPU& cpu);
    void RMB5_impl(CPU& cpu);
    void RMB6_impl(CPU& cpu);
    void RMB7_impl(CPU& cpu);
    void SMB0_impl(CPU& cpu);
    void SMB1_impl(CPU& cpu);
    void SMB2_impl(CPU& cpu);
    void SMB3_impl(CPU& cpu);
    void SMB4_impl(CPU& cpu);
    void SMB5_impl(CPU& cpu);
    void SMB6_impl(CPU& cpu);
    void SMB7_impl(CPU& cpu);
    void ROL_ABS_impl(CPU& cpu);
    void ROL_ABS_X_impl(CPU& cpu);
    void ROL_IMM_impl(CPU& cpu);
    void ROL_ZP_impl(CPU& cpu);
    void ROL_ZP_X_impl(CPU& cpu);
    void ROR_ABS_impl(CPU& cpu);
    void ROR_ABS_X_impl(CPU& cpu);
    void ROR_IMM_impl(CPU& cpu);
    void ROR_ZP_impl(CPU& cpu);
    void ROR_ZP_X_impl(CPU& cpu);
    void RTI_impl(CPU& cpu);
    void RTS_impl(CPU& cpu);
    void SBC_ABS_impl(CPU& cpu);
    void SBC_ABS_X_impl(CPU& cpu);
    void SBC_ABS_Y_impl(CPU& cpu);
    void SBC_IMM_impl(CPU& cpu);
    void SBC_ZP_impl(CPU& cpu);
    void SBC_ZP_IND_impl(CPU& cpu);
    void SBC_ZP_X_impl(CPU& cpu);
    void SBC_ZP_X_IND_impl(CPU& cpu);
    void SBC_ZP_IND_Y_impl(CPU& cpu);
    void SEC_impl(CPU& cpu);
    void SED_impl(CPU& cpu);
    void SEI_impl(CPU& cpu);
    void STA_ABS_impl(CPU& cpu);
    void STA_ABS_X_impl(CPU& cpu);
    void STA_ABS_Y_impl(CPU& cpu);
    void STA_ZP_impl(CPU& cpu);
    void STA_ZP_IND_impl(CPU& cpu);
    void STA_ZP_X_impl(CPU& cpu);
    void STA_ZP_X_IND_impl(CPU& cpu);
    void STA_ZP_IND_Y_impl(CPU& cpu);
    void STX_ABS_impl(CPU& cpu);
    void STX_ZP_impl(CPU& cpu);
    void STX_ZP_Y_impl(CPU& cpu);
    void STY_ABS_impl(CPU& cpu);
    void STY_ZP_impl(CPU& cpu);
    void STY_ZP_X_impl(CPU& cpu);
    void STZ_ABS_impl(CPU& cpu);
    void STZ_ABS_X_impl(CPU& cpu);
    void STZ_ZP_impl(CPU& cpu);
    void STZ_ZP_X_impl(CPU& cpu);
    void STP_impl(CPU& cpu);
    void TRB_ABS_impl(CPU& cpu);
    void TRB_ZP_impl(CPU& cpu);
    void TSB_ABS_impl(CPU& cpu);
    void TSB_ZP_impl(CPU& cpu);
    void TAX_impl(CPU& cpu);
    void TAY_impl(CPU& cpu);
    void TSX_impl(CPU& cpu);
    void TXA_impl(CPU& cpu);
    void TXS_impl(CPU& cpu);
    void TYA_impl(CPU& cpu);
    void WAI_impl(CPU& cpu);
}//namespace InstructionImpl

const std::map<Instruction, InstructionImplFun*> InstructionMap = {
    { Instruction::ADC_ABS,      (InstructionImplFun*)&instruction_impl::ADC_ABS_impl },
    { Instruction::ADC_ABS_X,    (InstructionImplFun*)&instruction_impl::ADC_ABS_X_impl },
    { Instruction::ADC_ABS_Y,    (InstructionImplFun*)&instruction_impl::ADC_ABS_Y_impl },
    { Instruction::ADC_IMM,      (InstructionImplFun*)&instruction_impl::ADC_IMM_impl },
    { Instruction::ADC_ZP,       (InstructionImplFun*)&instruction_impl::ADC_ZP_impl },
    { Instruction::ADC_ZP_IND,   (InstructionImplFun*)&instruction_impl::ADC_ZP_IND_impl },
    { Instruction::ADC_ZP_X,     (InstructionImplFun*)&instruction_impl::ADC_ZP_X_impl },
    { Instruction::ADC_ZP_X_IND, (InstructionImplFun*)&instruction_impl::ADC_ZP_X_IND_impl },
    { Instruction::ADC_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::ADC_ZP_IND_Y_impl },
    { Instruction::AND_ABS,      (InstructionImplFun*)&instruction_impl::AND_ABS_impl },
    { Instruction::AND_ABS_X,    (InstructionImplFun*)&instruction_impl::AND_ABS_X_impl },
    { Instruction::AND_ABS_Y,    (InstructionImplFun*)&instruction_impl::AND_ABS_Y_impl },
    { Instruction::AND_IMM,      (InstructionImplFun*)&instruction_impl::AND_IMM_impl },
    { Instruction::AND_ZP,       (InstructionImplFun*)&instruction_impl::AND_ZP_impl },
    { Instruction::AND_ZP_IND,   (InstructionImplFun*)&instruction_impl::AND_ZP_IND_impl },
    { Instruction::AND_ZP_X,     (InstructionImplFun*)&instruction_impl::AND_ZP_X_impl },
    { Instruction::AND_ZP_X_IND, (InstructionImplFun*)&instruction_impl::AND_ZP_X_IND_impl },
    { Instruction::AND_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::AND_ZP_IND_Y_impl },
    { Instruction::ASL_ABS,      (InstructionImplFun*)&instruction_impl::ASL_ABS_impl },
    { Instruction::ASL_ABS_X,    (InstructionImplFun*)&instruction_impl::ASL_ABS_X_impl },
    { Instruction::ASL_ACC,      (InstructionImplFun*)&instruction_impl::ASL_ACC_impl },
    { Instruction::ASL_ZP,       (InstructionImplFun*)&instruction_impl::ASL_ZP_impl },
    { Instruction::ASL_ZP_X,     (InstructionImplFun*)&instruction_impl::ASL_ZP_X_impl },
    { Instruction::BBR0,         (InstructionImplFun*)&instruction_impl::BBR0_impl },
    { Instruction::BBR1,         (InstructionImplFun*)&instruction_impl::BBR1_impl },
    { Instruction::BBR2,         (InstructionImplFun*)&instruction_impl::BBR2_impl },
    { Instruction::BBR3,         (InstructionImplFun*)&instruction_impl::BBR3_impl },
    { Instruction::BBR4,         (InstructionImplFun*)&instruction_impl::BBR4_impl },
    { Instruction::BBR5,         (InstructionImplFun*)&instruction_impl::BBR5_impl },
    { Instruction::BBR6,         (InstructionImplFun*)&instruction_impl::BBR6_impl },
    { Instruction::BBR7,         (InstructionImplFun*)&instruction_impl::BBR7_impl },
    { Instruction::BBS0,         (InstructionImplFun*)&instruction_impl::BBS0_impl },
    { Instruction::BBS1,         (InstructionImplFun*)&instruction_impl::BBS1_impl },
    { Instruction::BBS2,         (InstructionImplFun*)&instruction_impl::BBS2_impl },
    { Instruction::BBS3,         (InstructionImplFun*)&instruction_impl::BBS3_impl },
    { Instruction::BBS4,         (InstructionImplFun*)&instruction_impl::BBS4_impl },
    { Instruction::BBS5,         (InstructionImplFun*)&instruction_impl::BBS5_impl },
    { Instruction::BBS6,         (InstructionImplFun*)&instruction_impl::BBS6_impl },
    { Instruction::BBS7,         (InstructionImplFun*)&instruction_impl::BBS7_impl },
    { Instruction::BCC,          (InstructionImplFun*)&instruction_impl::BCC_impl },
    { Instruction::BCS,          (InstructionImplFun*)&instruction_impl::BCS_impl },
    { Instruction::BEQ,          (InstructionImplFun*)&instruction_impl::BEQ_impl },
    { Instruction::BNE,          (InstructionImplFun*)&instruction_impl::BNE_impl },
    { Instruction::BPL,          (InstructionImplFun*)&instruction_impl::BPL_impl },
    { Instruction::BMI,          (InstructionImplFun*)&instruction_impl::BMI_impl },
    { Instruction::BVC,          (InstructionImplFun*)&instruction_impl::BVC_impl },
    { Instruction::BVS,          (InstructionImplFun*)&instruction_impl::BVS_impl },
    { Instruction::BRA,          (InstructionImplFun*)&instruction_impl::BRA_impl },
    { Instruction::BIT_ABS,      (InstructionImplFun*)&instruction_impl::BIT_ABS_impl },
    { Instruction::BIT_ABS_X,    (InstructionImplFun*)&instruction_impl::BIT_ABS_X_impl },
    { Instruction::BIT_IMM,      (InstructionImplFun*)&instruction_impl::BIT_IMM_impl },
    { Instruction::BIT_ZP,       (InstructionImplFun*)&instruction_impl::BIT_ZP_impl },
    { Instruction::BIT_ZP_X,     (InstructionImplFun*)&instruction_impl::BIT_ZP_X_impl },
    { Instruction::BRK,          (InstructionImplFun*)&instruction_impl::BRK_impl },
    { Instruction::CLC,          (InstructionImplFun*)&instruction_impl::CLC_impl },
    { Instruction::CLD,          (InstructionImplFun*)&instruction_impl::CLD_impl },
    { Instruction::CLI,          (InstructionImplFun*)&instruction_impl::CLI_impl },
    { Instruction::CLV,          (InstructionImplFun*)&instruction_impl::CLV_impl },
    { Instruction::CMP_ABS,      (InstructionImplFun*)&instruction_impl::CMP_ABS_impl },
    { Instruction::CMP_ABS_X,    (InstructionImplFun*)&instruction_impl::CMP_ABS_X_impl },
    { Instruction::CMP_ABS_Y,    (InstructionImplFun*)&instruction_impl::CMP_ABS_Y_impl },
    { Instruction::CMP_IMM,      (InstructionImplFun*)&instruction_impl::CMP_IMM_impl },
    { Instruction::CMP_ZP,       (InstructionImplFun*)&instruction_impl::CMP_ZP_impl },
    { Instruction::CMP_ZP_IND,   (InstructionImplFun*)&instruction_impl::CMP_ZP_IND_impl },
    { Instruction::CMP_ZP_X,     (InstructionImplFun*)&instruction_impl::CMP_ZP_X_impl },
    { Instruction::CMP_ZP_X_IND, (InstructionImplFun*)&instruction_impl::CMP_ZP_X_IND_impl },
    { Instruction::CMP_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::CMP_ZP_IND_Y_impl },
    { Instruction::CPX_ABS,      (InstructionImplFun*)&instruction_impl::CPX_ABS_impl },
    { Instruction::CPX_IMM,      (InstructionImplFun*)&instruction_impl::CPX_IMM_impl },
    { Instruction::CPX_ZP,       (InstructionImplFun*)&instruction_impl::CPX_ZP_impl },
    { Instruction::CPY_ABS,      (InstructionImplFun*)&instruction_impl::CPY_ABS_impl },
    { Instruction::CPY_IMM,      (InstructionImplFun*)&instruction_impl::CPY_IMM_impl },
    { Instruction::CPY_ZP,       (InstructionImplFun*)&instruction_impl::CPY_ZP_impl },
    { Instruction::DEC_ABS,      (InstructionImplFun*)&instruction_impl::DEC_ABS_impl },
    { Instruction::DEC_ABS_X,    (InstructionImplFun*)&instruction_impl::DEC_ABS_X_impl },
    { Instruction::DEC_ZP,       (InstructionImplFun*)&instruction_impl::DEC_ZP_impl },
    { Instruction::DEC_ZP_X,     (InstructionImplFun*)&instruction_impl::DEC_ZP_X_impl },
    { Instruction::DEC_ACC,      (InstructionImplFun*)&instruction_impl::DEC_ACC_impl },
    { Instruction::DEX,          (InstructionImplFun*)&instruction_impl::DEX_impl },
    { Instruction::DEY,          (InstructionImplFun*)&instruction_impl::DEY_impl },
    { Instruction::EOR_ABS,      (InstructionImplFun*)&instruction_impl::EOR_ABS_impl },
    { Instruction::EOR_ABS_X,    (InstructionImplFun*)&instruction_impl::EOR_ABS_X_impl },
    { Instruction::EOR_ABS_Y,    (InstructionImplFun*)&instruction_impl::EOR_ABS_Y_impl },
    { Instruction::EOR_IMM,      (InstructionImplFun*)&instruction_impl::EOR_IMM_impl },
    { Instruction::EOR_ZP,       (InstructionImplFun*)&instruction_impl::EOR_ZP_impl },
    { Instruction::EOR_ZP_IND,   (InstructionImplFun*)&instruction_impl::EOR_ZP_IND_impl },
    { Instruction::EOR_ZP_X,     (InstructionImplFun*)&instruction_impl::EOR_ZP_X_impl },
    { Instruction::EOR_ZP_X_IND, (InstructionImplFun*)&instruction_impl::EOR_ZP_X_IND_impl },
    { Instruction::EOR_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::EOR_ZP_IND_Y_impl },
    { Instruction::INC_ABS,      (InstructionImplFun*)&instruction_impl::INC_ABS_impl },
    { Instruction::INC_ABS_X,    (InstructionImplFun*)&instruction_impl::INC_ABS_X_impl },
    { Instruction::INC_ZP,       (InstructionImplFun*)&instruction_impl::INC_ZP_impl },
    { Instruction::INC_ZP_X,     (InstructionImplFun*)&instruction_impl::INC_ZP_X_impl },
    { Instruction::INC_ACC,      (InstructionImplFun*)&instruction_impl::INC_ACC_impl },
    { Instruction::INX,          (InstructionImplFun*)&instruction_impl::INX_impl },
    { Instruction::INY,          (InstructionImplFun*)&instruction_impl::INY_impl },
    { Instruction::JMP_ABS,      (InstructionImplFun*)&instruction_impl::JMP_ABS_impl },
    { Instruction::JMP_ABS_IND,  (InstructionImplFun*)&instruction_impl::JMP_ABS_IND_impl },
    { Instruction::JMP_ABS_X_IND,(InstructionImplFun*)&instruction_impl::JMP_ABS_X_IND_impl },
    { Instruction::JSR,          (InstructionImplFun*)&instruction_impl::JSR_impl },
    { Instruction::LDA_ABS,      (InstructionImplFun*)&instruction_impl::LDA_ABS_impl },
    { Instruction::LDA_ABS_X,    (InstructionImplFun*)&instruction_impl::LDA_ABS_X_impl },
    { Instruction::LDA_ABS_Y,    (InstructionImplFun*)&instruction_impl::LDA_ABS_Y_impl },
    { Instruction::LDA_IMM,      (InstructionImplFun*)&instruction_impl::LDA_IMM_impl },
    { Instruction::LDA_ZP,       (InstructionImplFun*)&instruction_impl::LDA_ZP_impl },
    { Instruction::LDA_ZP_IND,   (InstructionImplFun*)&instruction_impl::LDA_ZP_IND_impl },
    { Instruction::LDA_ZP_X,     (InstructionImplFun*)&instruction_impl::LDA_ZP_X_impl },
    { Instruction::LDA_ZP_X_IND, (InstructionImplFun*)&instruction_impl::LDA_ZP_X_IND_impl },
    { Instruction::LDA_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::LDA_ZP_IND_Y_impl },
    { Instruction::LDX_ABS,      (InstructionImplFun*)&instruction_impl::LDX_ABS_impl },
    { Instruction::LDX_ABS_Y,    (InstructionImplFun*)&instruction_impl::LDX_ABS_Y_impl },
    { Instruction::LDX_IMM,      (InstructionImplFun*)&instruction_impl::LDX_IMM_impl },
    { Instruction::LDX_ZP,       (InstructionImplFun*)&instruction_impl::LDX_ZP_impl },
    { Instruction::LDX_ZP_Y,     (InstructionImplFun*)&instruction_impl::LDX_ZP_Y_impl },
    { Instruction::LDY_ABS,      (InstructionImplFun*)&instruction_impl::LDY_ABS_impl },
    { Instruction::LDY_ABS_X,    (InstructionImplFun*)&instruction_impl::LDY_ABS_X_impl },
    { Instruction::LDY_IMM,      (InstructionImplFun*)&instruction_impl::LDY_IMM_impl },
    { Instruction::LDY_ZP,       (InstructionImplFun*)&instruction_impl::LDY_ZP_impl },
    { Instruction::LDY_ZP_X,     (InstructionImplFun*)&instruction_impl::LDY_ZP_X_impl },
    { Instruction::LSR_ABS,      (InstructionImplFun*)&instruction_impl::LSR_ABS_impl },
    { Instruction::LSR_ABS_X,    (InstructionImplFun*)&instruction_impl::LSR_ABS_X_impl },
    { Instruction::LSR_ACC,      (InstructionImplFun*)&instruction_impl::LSR_ACC_impl },
    { Instruction::LSR_ZP,       (InstructionImplFun*)&instruction_impl::LSR_ZP_impl },
    { Instruction::LSR_ZP_X,     (InstructionImplFun*)&instruction_impl::LSR_ZP_X_impl },
    { Instruction::NOP,          (InstructionImplFun*)&instruction_impl::NOP_impl },
    { Instruction::ORA_ABS,      (InstructionImplFun*)&instruction_impl::ORA_ABS_impl },
    { Instruction::ORA_ABS_X,    (InstructionImplFun*)&instruction_impl::ORA_ABS_X_impl },
    { Instruction::ORA_ABS_Y,    (InstructionImplFun*)&instruction_impl::ORA_ABS_Y_impl },
    { Instruction::ORA_IMM,      (InstructionImplFun*)&instruction_impl::ORA_IMM_impl },
    { Instruction::ORA_ZP,       (InstructionImplFun*)&instruction_impl::ORA_ZP_impl },
    { Instruction::ORA_ZP_IND,   (InstructionImplFun*)&instruction_impl::ORA_ZP_IND_impl },
    { Instruction::ORA_ZP_X,     (InstructionImplFun*)&instruction_impl::ORA_ZP_X_impl },
    { Instruction::ORA_ZP_X_IND, (InstructionImplFun*)&instruction_impl::ORA_ZP_X_IND_impl },
    { Instruction::ORA_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::ORA_ZP_IND_Y_impl },
    { Instruction::PHA,          (InstructionImplFun*)&instruction_impl::PHA_impl },
    { Instruction::PHP,          (InstructionImplFun*)&instruction_impl::PHP_impl },
    { Instruction::PHX,          (InstructionImplFun*)&instruction_impl::PHX_impl },
    { Instruction::PHY,          (InstructionImplFun*)&instruction_impl::PHY_impl },
    { Instruction::PLA,          (InstructionImplFun*)&instruction_impl::PLA_impl },
    { Instruction::PLP,          (InstructionImplFun*)&instruction_impl::PLP_impl },
    { Instruction::PLX,          (InstructionImplFun*)&instruction_impl::PLX_impl },
    { Instruction::PLY,          (InstructionImplFun*)&instruction_impl::PLY_impl },
    { Instruction::RMB0,         (InstructionImplFun*)&instruction_impl::RMB0_impl },
    { Instruction::RMB1,         (InstructionImplFun*)&instruction_impl::RMB1_impl },
    { Instruction::RMB2,         (InstructionImplFun*)&instruction_impl::RMB2_impl },
    { Instruction::RMB3,         (InstructionImplFun*)&instruction_impl::RMB3_impl },
    { Instruction::RMB4,         (InstructionImplFun*)&instruction_impl::RMB4_impl },
    { Instruction::RMB5,         (InstructionImplFun*)&instruction_impl::RMB5_impl },
    { Instruction::RMB6,         (InstructionImplFun*)&instruction_impl::RMB6_impl },
    { Instruction::RMB7,         (InstructionImplFun*)&instruction_impl::RMB7_impl },
    { Instruction::SMB0,         (InstructionImplFun*)&instruction_impl::SMB0_impl },
    { Instruction::SMB1,         (InstructionImplFun*)&instruction_impl::SMB1_impl },
    { Instruction::SMB2,         (InstructionImplFun*)&instruction_impl::SMB2_impl },
    { Instruction::SMB3,         (InstructionImplFun*)&instruction_impl::SMB3_impl },
    { Instruction::SMB4,         (InstructionImplFun*)&instruction_impl::SMB4_impl },
    { Instruction::SMB5,         (InstructionImplFun*)&instruction_impl::SMB5_impl },
    { Instruction::SMB6,         (InstructionImplFun*)&instruction_impl::SMB6_impl },
    { Instruction::SMB7,         (InstructionImplFun*)&instruction_impl::SMB7_impl },
    { Instruction::ROL_ABS,      (InstructionImplFun*)&instruction_impl::ROL_ABS_impl },
    { Instruction::ROL_ABS_X,    (InstructionImplFun*)&instruction_impl::ROL_ABS_X_impl },
    { Instruction::ROL_IMM,      (InstructionImplFun*)&instruction_impl::ROL_IMM_impl },
    { Instruction::ROL_ZP,       (InstructionImplFun*)&instruction_impl::ROL_ZP_impl },
    { Instruction::ROL_ZP_X,     (InstructionImplFun*)&instruction_impl::ROL_ZP_X_impl },
    { Instruction::ROR_ABS,      (InstructionImplFun*)&instruction_impl::ROR_ABS_impl },
    { Instruction::ROR_ABS_X,    (InstructionImplFun*)&instruction_impl::ROR_ABS_X_impl },
    { Instruction::ROR_IMM,      (InstructionImplFun*)&instruction_impl::ROR_IMM_impl },
    { Instruction::ROR_ZP,       (InstructionImplFun*)&instruction_impl::ROR_ZP_impl },
    { Instruction::ROR_ZP_X,     (InstructionImplFun*)&instruction_impl::ROR_ZP_X_impl },
    { Instruction::RTI,          (InstructionImplFun*)&instruction_impl::RTI_impl },
    { Instruction::RTS,          (InstructionImplFun*)&instruction_impl::RTS_impl },
    { Instruction::SBC_ABS,      (InstructionImplFun*)&instruction_impl::SBC_ABS_impl },
    { Instruction::SBC_ABS_X,    (InstructionImplFun*)&instruction_impl::SBC_ABS_X_impl },
    { Instruction::SBC_ABS_Y,    (InstructionImplFun*)&instruction_impl::SBC_ABS_Y_impl },
    { Instruction::SBC_IMM,      (InstructionImplFun*)&instruction_impl::SBC_IMM_impl },
    { Instruction::SBC_ZP,       (InstructionImplFun*)&instruction_impl::SBC_ZP_impl },
    { Instruction::SBC_ZP_IND,   (InstructionImplFun*)&instruction_impl::SBC_ZP_IND_impl },
    { Instruction::SBC_ZP_X,     (InstructionImplFun*)&instruction_impl::SBC_ZP_X_impl },
    { Instruction::SBC_ZP_X_IND, (InstructionImplFun*)&instruction_impl::SBC_ZP_X_IND_impl },
    { Instruction::SBC_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::SBC_ZP_IND_Y_impl },
    { Instruction::SEC,          (InstructionImplFun*)&instruction_impl::SEC_impl },
    { Instruction::SED,          (InstructionImplFun*)&instruction_impl::SED_impl },
    { Instruction::SEI,          (InstructionImplFun*)&instruction_impl::SEI_impl },
    { Instruction::STA_ABS,      (InstructionImplFun*)&instruction_impl::STA_ABS_impl },
    { Instruction::STA_ABS_X,    (InstructionImplFun*)&instruction_impl::STA_ABS_X_impl },
    { Instruction::STA_ABS_Y,    (InstructionImplFun*)&instruction_impl::STA_ABS_Y_impl },
    { Instruction::STA_ZP,       (InstructionImplFun*)&instruction_impl::STA_ZP_impl },
    { Instruction::STA_ZP_IND,   (InstructionImplFun*)&instruction_impl::STA_ZP_IND_impl },
    { Instruction::STA_ZP_X,     (InstructionImplFun*)&instruction_impl::STA_ZP_X_impl },
    { Instruction::STA_ZP_X_IND, (InstructionImplFun*)&instruction_impl::STA_ZP_X_IND_impl },
    { Instruction::STA_ZP_IND_Y, (InstructionImplFun*)&instruction_impl::STA_ZP_IND_Y_impl },
    { Instruction::STX_ABS,      (InstructionImplFun*)&instruction_impl::STX_ABS_impl },
    { Instruction::STX_ZP,       (InstructionImplFun*)&instruction_impl::STX_ZP_impl },
    { Instruction::STX_ZP_Y,     (InstructionImplFun*)&instruction_impl::STX_ZP_Y_impl },
    { Instruction::STY_ABS,      (InstructionImplFun*)&instruction_impl::STY_ABS_impl },
    { Instruction::STY_ZP,       (InstructionImplFun*)&instruction_impl::STY_ZP_impl },
    { Instruction::STY_ZP_X,     (InstructionImplFun*)&instruction_impl::STY_ZP_X_impl },
    { Instruction::STZ_ABS,      (InstructionImplFun*)&instruction_impl::STZ_ABS_impl },
    { Instruction::STZ_ABS_X,    (InstructionImplFun*)&instruction_impl::STZ_ABS_X_impl },
    { Instruction::STZ_ZP,       (InstructionImplFun*)&instruction_impl::STZ_ZP_impl },
    { Instruction::STZ_ZP_X,     (InstructionImplFun*)&instruction_impl::STZ_ZP_X_impl },
    { Instruction::STP,          (InstructionImplFun*)&instruction_impl::STP_impl },
    { Instruction::TRB_ABS,      (InstructionImplFun*)&instruction_impl::TRB_ABS_impl },
    { Instruction::TRB_ZP,       (InstructionImplFun*)&instruction_impl::TRB_ZP_impl },
    { Instruction::TSB_ABS,      (InstructionImplFun*)&instruction_impl::TSB_ABS_impl },
    { Instruction::TSB_ZP,       (InstructionImplFun*)&instruction_impl::TSB_ZP_impl },
    { Instruction::TAX,          (InstructionImplFun*)&instruction_impl::TAX_impl },
    { Instruction::TAY,          (InstructionImplFun*)&instruction_impl::TAY_impl },
    { Instruction::TSX,          (InstructionImplFun*)&instruction_impl::TSX_impl },
    { Instruction::TXA,          (InstructionImplFun*)&instruction_impl::TXA_impl },
    { Instruction::TXS,          (InstructionImplFun*)&instruction_impl::TXS_impl },
    { Instruction::TYA,          (InstructionImplFun*)&instruction_impl::TYA_impl },
    { Instruction::WAI,          (InstructionImplFun*)&instruction_impl::WAI_impl }
};

}

#endif//CPUEMU__EMU__MOS6502__INSTRUCTION_IMPL_HPP