#ifndef CPUEMU__W65C02S_HPP
#define CPUEMU__W65C02S_HPP

#include <common/types.hpp>

namespace emu::w65c02s
{

// Literals describing operations and associated opcodes
enum class Instruction : Byte
{
    //
    // A (b) next to the cycle cost of an instruction means 1 extra cycle is spent if a branch is taken.
    //
    // A (c) next to the cycle cost of an instruction means 1 extra cycle is spent if a branch is taken across page boundaries.
    //
    // A (d) next to the cycle cost of an instruction means 1 extra cycle is spent if the processor is in decimal mode.
    // This only affects the ADC and SBC instructions, and that extra cycle is used to correctly set the N and Z flags,
    // thus fixing the so-called decimal bug present on the original nMOS-based 6502.
    //
    // A (p) next to the cycle cost of an instruction means 1 extra cycle is spent if the calculation of the final 
    // target memory address incurs a page cross (i.e when a carry bit must added to the high byte of the address).
    //
    // A (w) next to the cycle cost of an instruction means up to 2 extra cycles may be spent waiting for an active input on
    // interrupt pins.
    //
    // All cycle costs shown are the effective cycle costs of instructions, that is the amount of cycles required in order to
    // fetch the opcode from memory into the instruction register, decode it, and execute it up until the point where the opcode 
    // of the next instruction may be fetched from memory.
    // This may indeed be done in parallel to the last cycle required to complete the current instruction, as most instructions 
    // do not require the external data bus in order to transfer their result to its target location. This means the external
    // data bus can instead be used to fetch the opcode of the next instruction simultaneously, thereby allowing some kind of
    // instruction-level parallelism.
    //
    // If the column "Pre-fetch next opcode?" says Yes for a given instruction, it means the actual cycle cost of that 
    // instruction is 1 more than its effective cost, but by the time it will have been executed entirely, the opcode of the 
    // next instruction will have already been fetched from memory, ready to be decoded.
    //

    // Add memory to accumulator with carry
    // [instr.]     = [opcode]  // [syntax]         // [effects]                    // [status flags]   // [cycle cost]     // Pre-fetch next opcode?
    ADC_IMM         = 0x69,     // ADC #$12         // A = A + 0x12           + C   // C,Z,        V,N  // 2    (d)         // Yes
    ADC_ABS         = 0x6D,     // ADC $1234        // A = A + M[0x1234]      + C   // C,Z,        V,N  // 4    (d)         // Yes
    ADC_ABS_X       = 0x7D,     // ADC $1234,X      // A = A + M[0x1234 + X]  + C   // C,Z,        V,N  // 4    (d,p)       // Yes
    ADC_ABS_Y       = 0x79,     // ADC $1234,Y      // A = A + M[0x1234 + Y]  + C   // C,Z,        V,N  // 4    (d,p)       // Yes
    ADC_ZP          = 0x65,     // ADC $12          // A = A + M[0x12]        + C   // C,Z,        V,N  // 3    (d)         // Yes
    ADC_ZP_IND      = 0x72,     // ADC ($12)        // A = A + M[M[0x12]]     + C   // C,Z,        V,N  // 5    (d)         // Yes
    ADC_ZP_X        = 0x75,     // ADC $12,X        // A = A + M[0x12 + X]    + C   // C,Z,        V,N  // 4    (d)         // Yes
    ADC_ZP_X_IND    = 0x61,     // ADC ($12,Y)      // A = A + M{M[0x12 + Y]] + C   // C,Z,        V,N  // 6    (d)         // Yes
    ADC_ZP_IND_Y    = 0x71,     // ADC ($12),Y      // A = A + M[M[0x12] + Y] + C   // C,Z,        V,N  // 5    (d,p)       // Yes

    // AND memory with accumulator
    // [instr.]     = [opcode]  // [syntax]         // [effects]                    // [status flags]   // [cycle cost]     // Pre-fetch next opcode?
    AND_IMM         = 0x29,     // AND #%00010010   // A = A & 0b00010010           //   Z,          N  // 2    (d)         // Yes
    AND_ABS         = 0x2D,     // AND $1234        // A = A & M[0x1234]            //   Z,          N  // 4    (d)         // Yes
    AND_ABS_X       = 0x3D,     // AND $1234,X      // A = A & M[0x1234 + X]        //   Z,          N  // 4    (d,p)       // Yes
    AND_ABS_Y       = 0x39,     // AND $1234,Y      // A = A & M[0x1234 + Y]        //   Z,          N  // 4    (d,p)       // Yes
    AND_ZP          = 0x25,     // AND $12          // A = A & M[0x12]              //   Z,          N  // 3    (d)         // Yes
    AND_ZP_IND      = 0x32,     // AND ($12)        // A = A & M[M[0x12]]           //   Z,          N  // 5    (d)         // Yes
    AND_ZP_X        = 0x35,     // AND $12,X        // A = A & M[0x12 + X]          //   Z,          N  // 4    (d)         // Yes
    AND_ZP_X_IND    = 0x21,     // AND ($12,Y)      // A = A & M{M[0x12 + Y]]       //   Z,          N  // 6    (d)         // Yes
    AND_ZP_IND_Y    = 0x31,     // AND ($12),Y      // A = A & M[M[0x12] + Y]       //   Z,          N  // 5    (d,p)       // Yes

    // Arithmetic shift one bit left, memory or accumulator
    // [instr.]     = [opcode]  // [syntax]         // [effects]                    // [status flags]   // [cycle cost]     // Pre-fetch next opcode?
    ASL_ABS         = 0x0E,     // ASL $1234        // A = A & M[0x1234]            // 
    ASL_ABS_X       = 0x1E,     // ASL $1234,X      // A = A & M[0x1234 + X]        // 
    ASL_ACC         = 0x0A,     // ASL              // A = A << 1                   // C,Z,          N  // 2                // 
    ASL_ZP          = 0x06,     // ASL $12          // A = A & M[0x12]              // 
    ASL_ZP_X        = 0x16,     // ASL $12,X        // A = A & M[0x12 + X]          // 

    // Branch on zero-page bit set/clear
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

    // Clear processor status flag
    CLC             = 0x18,     // Carry
    CLD             = 0xD8,     // Decimal mode
    CLI             = 0x58,     // IRQ disable
    CLV             = 0xB8,     // Overflow

    // Compare memory and accumulator
    CMP_ABS         = 0xCD,     // Absolute
    CMP_ABS_X       = 0xDD,     // Absolute indexed with X
    CMP_ABS_Y       = 0xD9,     // Absolute indexed with Y
    CMP_IMM         = 0xC9,     // Immediate
    CMP_ZP          = 0xC5,     // Zero page
    CMP_ZP_IND      = 0xD2,     // Zero page indirect
    CMP_ZP_X        = 0xD5,     // Zero page indexed with X
    CMP_ZP_X_IND    = 0xC1,     // Zero page indexed with X indirect
    CMP_ZP_IND_Y    = 0xD1,     // Zero page indirect indexed with Y

    // Compare memory and X
    CPX_ABS         = 0xEC,     // Absolute
    CPX_IMM         = 0xE0,     // Immediate
    CPX_ZP          = 0xE4,     // Zero page

    // Compare memory and Y
    CPY_ABS         = 0xCC,     // Absolute
    CPY_IMM         = 0xC0,     // Immediate
    CPY_ZP          = 0xC4,     // Zero page
    
    // Decrement memory
    DEC_ABS         = 0xCE,     // Absolute
    DEC_ABS_X       = 0xDE,     // Absolute indexed with X
    DEC_ZP          = 0xC6,     // Zero page
    DEC_ZP_X        = 0xD6,     // Zero page indexed with X
    // Decrement register
    DEC_ACC         = 0x3A,     // Accumulator
    DEX             = 0xCA,     // X
    DEY             = 0x88,     // Y

    // XOR memory with accumulator
    EOR_ABS         = 0x4D,     // Absolute
    EOR_ABS_X       = 0x5D,     // Absolute indexed with X
    EOR_ABS_Y       = 0x59,     // Absolute indexed with Y
    EOR_IMM         = 0x49,     // Immediate
    EOR_ZP          = 0x45,     // Zero page
    EOR_ZP_IND      = 0x42,     // Zero page indirect
    EOR_ZP_X        = 0x55,     // Zero page indexed with X
    EOR_ZP_X_IND    = 0x41,     // Zero page indexed with X indirect
    EOR_ZP_IND_Y    = 0x51,     // Zero page indirect indexed with Y

    // Increment memory
    INC_ABS         = 0xEE,     // Absolute
    INC_ABS_X       = 0xFE,     // Absolute indexed with X
    INC_ZP          = 0xE6,     // Zero page
    INC_ZP_X        = 0xF6,     // Zero page indexed with X
    // Increment register
    INC_ACC         = 0x1A,     // Accumulator
    INX             = 0xE8,     // X
    INY             = 0xC8,     // Y

    // Jump to address
    JMP_ABS         = 0x4C,     // Absolute
    JMP_ABS_IND     = 0x7C,     // Absolute indirect
    JMP_ABS_X_IND   = 0x6C,     // Absolute indexed with X indirect

    // Jump to subroutine
    JSR             = 0x20,

    // Load memory into accumulator
    LDA_ABS         = 0xAD,     // Absolute
    LDA_ABS_X       = 0xBD,     // Absolute indexed with X
    LDA_ABS_Y       = 0xB9,     // Absolute indexed with Y
    LDA_IMM         = 0xA9,     // Immediate
    LDA_ZP          = 0xA5,     // Zero page
    LDA_ZP_IND      = 0xB2,     // Zero page indirect
    LDA_ZP_X        = 0xB5,     // Zero page indexed with X
    LDA_ZP_X_IND    = 0xA1,     // Zero page indexed with X indirect
    LDA_ZP_IND_Y    = 0xB1,     // Zero page indirect indexed with Y

    // Load memory into X
    LDX_ABS         = 0xAE,     // Absolute
    LDX_ABS_Y       = 0xBE,     // Absolute indexed with Y
    LDX_IMM         = 0xA2,     // Immediate
    LDX_ZP          = 0xA6,     // Zero page
    LDX_ZP_Y        = 0xB6,     // Zero page indexed with Y

    // Load memory into Y
    LDY_ABS         = 0xAC,     // Absolute
    LDY_ABS_X       = 0xBC,     // Absolute indexed with X
    LDY_IMM         = 0xA0,     // Immediate
    LDY_ZP          = 0xA4,     // Zero page
    LDY_ZP_X        = 0xB4,     // Zero page indexed with X

    // Logical shift one bit right, memory or accumulator
    LSR_ABS         = 0x4E,     // Absolute
    LSR_ABS_X       = 0x5E,     // Absolute indexed with X
    LSR_ACC         = 0x4A,     // Accumulator
    LSR_ZP          = 0x46,     // Zero page
    LSR_ZP_X        = 0x56,     // Zero page indexed with X

    // No operation
    NOP             = 0xEA,

    // OR memory with accumulator
    ORA_ABS         = 0x0D,     // Absolute
    ORA_ABS_X       = 0x1D,     // Absolute indexed with X
    ORA_ABS_Y       = 0x19,     // Absolute indexed with Y
    ORA_IMM         = 0x09,     // Immediate
    ORA_ZP          = 0x05,     // Zero page
    ORA_ZP_IND      = 0x12,     // Zero page indirect
    ORA_ZP_X        = 0x15,     // Zero page indexed with X
    ORA_ZP_X_IND    = 0x01,     // Zero page indexed with X indirect
    ORA_ZP_IND_Y    = 0x11,     // Zero page indirect indexed with Y

    // Push registers on stack (stack pointer decrements)
    PHA             = 0x48,     // Accumulator
    PHP             = 0x08,     // Processor status
    PHX             = 0xDA,     // X
    PHY             = 0x5A,     // Y

    // Pull registers from stack (stack pointer increments)
    PLA             = 0x68,     // Accumulator
    PLP             = 0x28,     // Processor status
    PLX             = 0xFA,     // X
    PLY             = 0x7A,     // Y

    // Reet memory bit
    RMB0            = 0x07,
    RMB1            = 0x17,
    RMB2            = 0x27,
    RMB3            = 0x37,
    RMB4            = 0x47,
    RMB5            = 0x57,
    RMB6            = 0x67,
    RMB7            = 0x77,

    // Set memory bit
    SMB0            = 0x87,
    SMB1            = 0x97,
    SMB2            = 0xA7,
    SMB3            = 0xB7,
    SMB4            = 0xC7,
    SMB5            = 0xD7,
    SMB6            = 0xE7,
    SMB7            = 0xF7,

    // Rotate one bit left, memory or accumulator
    ROL_ABS         = 0x2E,     // Absolute
    ROL_ABS_X       = 0x3E,     // Absolute indexed with X
    ROL_IMM         = 0x2A,     // Immediate
    ROL_ZP          = 0x26,     // Zero page
    ROL_ZP_X        = 0x36,     // Zero page indexed with X

    // Rotate one bit right, memory or accumulator
    ROR_ABS         = 0x6E,     // Absolute
    ROR_ABS_X       = 0x7E,     // Absolute indexed with X
    ROR_IMM         = 0x6A,     // Immediate
    ROR_ZP          = 0x66,     // Zero page
    ROR_ZP_X        = 0x76,     // Zero page indexed with X

    // Return instructions
    RTI             = 0x40,     // from interrupt
    RTS             = 0x60,     // from subroutine

    // Substract memory from accumulator, with borrow (carry)
    SBC_ABS         = 0xED,     // Absolute
    SBC_ABS_X       = 0xFD,     // Absolute indexed with X
    SBC_ABS_Y       = 0xF9,     // Absolute indexed with Y
    SBC_IMM         = 0xE9,     // Immediate
    SBC_ZP          = 0xE5,     // Zero page
    SBC_ZP_IND      = 0xF2,     // Zero page indirect
    SBC_ZP_X        = 0xF5,     // Zero page indexed with X
    SBC_ZP_X_IND    = 0xE1,     // Zero page indexed with X indirect
    SBC_ZP_IND_Y    = 0xF1,     // Zero page indirect indexed with Y

    // Set processor status flag
    SEC             = 0x38,     // Carry
    SED             = 0xF8,     // Decimal mode
    SEI             = 0x78,     // IRQ disable

    // Store accumulator into memory
    STA_ABS         = 0x8D,     // Absolute
    STA_ABS_X       = 0x9D,     // Absolute indexed with X
    STA_ABS_Y       = 0x99,     // Absolute indexed with Y
    STA_ZP          = 0x85,     // Zero page
    STA_ZP_IND      = 0x92,     // Zero page indirect
    STA_ZP_X        = 0x95,     // Zero page indexed with X
    STA_ZP_X_IND    = 0x81,     // Zero page indexed with X indirect
    STA_ZP_IND_Y    = 0x91,     // Zero page indirect indexed with Y

    // Store X into memory
    STX_ABS         = 0x8E,     // Absolute
    STX_ZP          = 0x86,     // Zero page
    STX_ZP_Y        = 0x96,     // Zero page indexed with Y

    // Store Y into memory
    STY_ABS         = 0x8C,     // Absolute
    STY_ZP          = 0x84,     // Zero page
    STY_ZP_X        = 0x94,     // Zero page indexed with X

    // Store zero into memory
    STZ_ABS         = 0x9C,     // Absolute
    STZ_ABS_X       = 0x9E,     // Absolute indexed with X
    STZ_ZP          = 0x64,     // Zero page
    STZ_ZP_X        = 0x74,     // Zero page indexed with X

    // Stop
    STP             = 0xDB,

    // Test and reset memory bit
    TRB_ABS         = 0x1C,     // Absolute
    TRB_ZP          = 0x14,     // Zero page

    // Test and set memory bit
    TSB_ABS         = 0x0C,     // Absolute
    TSB_ZP          = 0x04,     // Zero page

    // Register transfers
    TAX             = 0xAA,     // Accumulator to X
    TAY             = 0xA8,     // Accumulator to Y
    TSX             = 0xBA,     // Stack to X
    TXA             = 0x8A,     // X to accumulator
    TXS             = 0x9A,     // X to stack
    TYA             = 0x98,     // Y to accumulator
    
    // Wait for interrupt
    WAI             = 0xCB
};

using Ins = Instruction;

}//namespace emu::w65c02s


#endif//CPUEMU__W65C02S_HPP