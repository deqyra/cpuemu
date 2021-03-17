#ifndef CPUEMU__EMU__MPU6502_HPP
#define CPUEMU__EMU__MPU6502_HPP

#include <emu/common/types.hpp>

namespace emu::mpu6502
{

// Literals describing operations and associated opcodes
enum class Instruction : Byte
{
    // Add memory to accumulator with carry
    ADC_ABS         = 0x6D,     // Absolute
    ADC_ABS_X       = 0x7D,     // Absolute indexed with X
    ADC_ABS_Y       = 0x79,     // Absolute indexed with Y
    ADC_IMM         = 0x69,     // Immediate
    ADC_ZP          = 0x65,     // Zero page
    ADC_ZP_IND      = 0x72,     // Zero page indirect
    ADC_ZP_X        = 0x75,     // Zero page indexed with X
    ADC_ZP_X_IND    = 0x61,     // Zero page indexed with X indirect
    ADC_ZP_IND_Y    = 0x71,     // Zero page indirect indexed with Y

    // AND memory with accumulator
    AND_ABS         = 0x2D,     // Absolute
    AND_ABS_X       = 0x3D,     // Absolute indexed with X
    AND_ABS_Y       = 0x39,     // Absolute indexed with Y
    AND_IMM         = 0x29,     // Immediate
    AND_ZP          = 0x25,     // Zero page
    AND_ZP_IND      = 0x32,     // Zero page indirect
    AND_ZP_X        = 0x35,     // Zero page indexed with X
    AND_ZP_X_IND    = 0x21,     // Zero page indexed with X indirect
    AND_ZP_IND_Y    = 0x31,     // Zero page indirect indexed with Y

    // Arithmetic shift one bit left, memory or accumulator
    AND_ABS         = 0x0E,     // Absolute
    AND_ABS_X       = 0x1E,     // Absolute indexed with X
    AND_ACC         = 0x0A,     // Accumulator
    AND_ZP          = 0x06,     // Zero page
    AND_ZP_X        = 0x16,     // Zero page indexed with X

    // Branch on bit set/reset
    BBR0            = 0x0F,
    BBR1            = 0x1F,
    BBR2            = 0x2F,
    BBR3            = 0x3F,
    BBR4            = 0x4F,
    BBR5            = 0x5F,
    BBR6            = 0x6F,
    BBR7            = 0x7F,
    BBS0            = 0x8F,
    BBS1            = 0x9F,
    BBS2            = 0xAF,
    BBS3            = 0xBF,
    BBS4            = 0xCF,
    BBS5            = 0xDF,
    BBS6            = 0xEF,
    BBS7            = 0xFF,

    // More branch instructions
    BCC             = 0x90,     // Branch on carry clear (Pc = 0)
    BCS             = 0xB0,     // Branch on carry set (Pc = 1)
    BEQ             = 0xF0,     // Branch if equal (Pz = 1)
    BNE             = 0xD0,     // Branch if not equal (Pz = 0)
    BPL             = 0x10,     // Branch if result plus (Pn = 0)
    BMI             = 0x30,     // Branch if result minus (Pn = 1)
    BVC             = 0x50,     // Branch on overflow clear (Pc = 0)
    BVS             = 0x70,     // Branch on overflow set (Pc = 1)
    BRA             = 0x80,     // Branch always

    // Bit test
    BIT_ABS         = 0x2C,     // Absolute
    BIT_ABS_X       = 0x3C,     // Absolute indexed with X
    BIT_IMM         = 0x89,     // Immediate
    BIT_ZP          = 0x24,     // Zero page
    BIT_ZP_X        = 0x34,     // Zero page indexed with X

    // Break
    BRK             = 0x00,
};

using Ins = Instruction;

}//namespace emu::mpu6502


#endif//CPUEMU__EMU__MPU6502_HPP