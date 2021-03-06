#include <catch2/catch2.hpp>

#include <vector>

#include <common/types.hpp>
#include <w65c02s/execution_wrapper.hpp>
#include <w65c02s/instruction.hpp>
#include <w65c02s/instruction_info.hpp>

#include "../macros.hpp"

#define TAGS "[w65c02s][instruction][arithmetic]"

namespace emu::w65c02s
{

TEST_CASE("Instruction::ADC", TAGS)
{
    using namespace emu;
    using Ins = w65c02s::Instruction;
    using w65c02s::ExecutionWrapper;
    ExecutionWrapper ex;

    constexpr uint16_t DataAddress = 0x0200;
    const std::vector<Byte> Data = {
        0x05,   0x04,   0x08,   0x02,   0x07,   0x08,   0x09,   0x0A,   //0x0200
        0x3A,   0x7D,   0x10,   0x02,   0x6F,   0x2B,   0x36,   0x81,   //0x0208
        0x71,   0x2B,   0x18,   0x02,   0x83,   0x7D,   0x11,   0xFF,   //0x0210
        0x51,   0xC6,   0x04,   0x02,   0xE5,   0x70,   0x96,   0xD6    //0x0218
    };                                                                  //0x0220
    ex.registerMemory(Data, DataAddress);

    const std::vector<Byte> ZPData = {
        0x36,   0x12,   0xBD,   0x03,   0xA3,   0xFA,   0x08,   0x02,   //0x0000
        0x45,   0x5E,   0xB9,   0xBF,   0x16,   0x87,   0x2C,   0x1D,   //0x0008
        0x19,   0xD2,   0x94,   0x06,   0xB6,   0x87,   0x86,   0xA3,   //0x0010
        0xFD,   0xBB,   0xE4,   0x27,   0xFC,   0xF4,   0x18,   0x02    //0x0018
    };                                                                  //0x0020
    ex.registerMemory(ZPData, 0x0000);

    constexpr uint16_t StartAddress = 0x0400;

    SECTION("Immediate operand")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_IMM);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x03,           // Add        0x03      to   A  (2 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        uint64_t n = ex.instructionStep();  // ADC #$03
        
        CHECK(n == it->second.minCycleCost);
        // A should now be 0x05
        REQUIRE(ex.cpu.registers.A == 0x05);
    }

    SECTION("Zero-page addressing")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ZP);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::ADC_ZP,          0x05,           // Add     [0x0005]     to   A  (3 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        uint64_t n = ex.instructionStep();  // ADC $05

        CHECK(n == it->second.minCycleCost);
        // A should now be 0xFC
        REQUIRE(ex.cpu.registers.A == 0xFC);
    }

    SECTION("Zero-page addressing, indexed by X")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ZP_X);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::LDX_IMM,         0x13,           // Load       0x13      into X  (2 cycles)
            (Byte)Ins::ADC_ZP_X,        0x06,           // Add      0x0006 + X  to   A  (4 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        ex.instructionStep();               // LDX #$13
        uint64_t n = ex.instructionStep();  // ADC $06,X

        CHECK(n == it->second.minCycleCost);
        // A should now be 0xBD
        REQUIRE(ex.cpu.registers.A == 0xBD);
    }

    SECTION("Absolute addressing")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ABS);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::ADC_ABS,         0x00,   0x02,   // Add     [0x0200]     to   A  (4 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        uint64_t n = ex.instructionStep();  // ADC $0200

        CHECK(n == it->second.minCycleCost);
        // A should now be 0x07
        REQUIRE(ex.cpu.registers.A == 0x07);
    }

    SECTION("Absolute addressing, indexed by X")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ABS_X);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::LDX_IMM,         0x03,           // Load       0x03      into X  (2 cycles)
            (Byte)Ins::ADC_ABS_X,       0x00,   0x02,   // Add     [0x0200 + X] to   A  (4 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        ex.instructionStep();               // LDX #$03
        uint64_t n = ex.instructionStep();  // ADC $0200,X

        CHECK(n == it->second.minCycleCost);
        // A should now be 0x04
        REQUIRE(ex.cpu.registers.A == 0x04);
    }

    SECTION("Absolute addressing, indexed by Y")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ABS_Y);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::LDY_IMM,         0x05,           // Load       0x05      into Y  (2 cycles)
            (Byte)Ins::ADC_ABS_Y,       0x00,   0x02,   // Add     [0x0200 + Y] to   A  (4 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        ex.instructionStep();               // LDY #$05
        uint64_t n = ex.instructionStep();  // ADC $0200,X

        CHECK(n == it->second.minCycleCost);
        // A should now be 0x0A
        REQUIRE(ex.cpu.registers.A == 0x0A);
    }

    SECTION("Zero-page addressing, indirect")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ZP_IND);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::ADC_ZP_IND,      0x06,           // Add    [[0x0006]]    to   A  (5 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        uint64_t n = ex.instructionStep();  // ADC ($06)

        CHECK(n == it->second.minCycleCost);
        // A should now be 0x3C
        REQUIRE(ex.cpu.registers.A == 0x3C);
    }

    SECTION("Zero-page addressing indexed by X, indirect")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ZP_X_IND);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::LDX_IMM,         0x13,           // Load       0x13      into X  (2 cycles)
            (Byte)Ins::ADC_ZP_X_IND,    0x0B,           // Add    [[0x000B+X]]  to   A  (6 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        ex.instructionStep();               // LDX #$13
        uint64_t n = ex.instructionStep();  // ADC ($0B,X)

        CHECK(n == it->second.minCycleCost);
        // A should now be 0x53
        REQUIRE(ex.cpu.registers.A == 0x53);
    }

    SECTION("Zero-page addressing indirect, indexed by Y")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ZP_IND_Y);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02      into A  (2 cycles)
            (Byte)Ins::LDY_IMM,         0x04,           // Load       0x04      into Y  (2 cycles)
            (Byte)Ins::ADC_ZP_IND_Y,    0x1E,           // Add    [[0x001E]+Y]  to   A  (6 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$02
        ex.instructionStep();               // LDY #$04
        uint64_t n = ex.instructionStep();  // ADC ($1E),Y

        CHECK(n == it->second.minCycleCost);
        // A should now be 0xE7
        REQUIRE(ex.cpu.registers.A == 0xE7);
    }

    SECTION("Decimal mode (immediate operand)")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_IMM);

        const std::vector<Byte> Program = {
            (Byte)Ins::SED,                             // Set decimal flag             (2 cycles)
            (Byte)Ins::LDA_IMM,         0x19,           // Load       0x19      into A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x27,           // Add        0x27      to   A  (3 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // SED
        ex.instructionStep();               // LDA #$19
        uint64_t n = ex.instructionStep();  // ADC #$27
        
        CHECK(n == it->second.maxCycleCost);
        // A should now be 0x46
        REQUIRE(ex.cpu.registers.A == 0x46);
    }

    SECTION("Carry flag")
    {
        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x19,           // Load       0x19      into A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x70,           // Add        0x70      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x76,           // Add        0x76      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x01,           // Add        0x01      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x01,           // Add        0x01      to   A  (2 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$19

        ex.instructionStep();               // ADC #$70
        // A should now be 0x89, no carry
        REQUIRE(ex.cpu.registers.A == 0x89);
        REQUIRE(!ex.cpu.registers.P.c);

        ex.instructionStep();               // ADC #$76
        // A should now be 0xFF, no carry
        REQUIRE(ex.cpu.registers.A == 0xFF);
        REQUIRE(!ex.cpu.registers.P.c);

        ex.instructionStep();               // ADC #$01
        // A should now be 0x00, with carry
        REQUIRE(ex.cpu.registers.A == 0x00);
        REQUIRE(ex.cpu.registers.P.c);

        ex.instructionStep();               // ADC #$01 (and carry from previous ADC)
        // A should now be 0x02, no carry
        REQUIRE(ex.cpu.registers.A == 0x02);
        REQUIRE(!ex.cpu.registers.P.c);
    }

    SECTION("Overflow flag")
    {
        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x19,           // Load       0x19      into A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x60,           // Add        0x60      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x76,           // Add        0x76      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0xF5,           // Add        0xF5      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x25,           // Add        0x25      to   A  (2 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$19

        ex.instructionStep();               // ADC #$60
        // A should now be 0x79, no overflow
        REQUIRE(ex.cpu.registers.A == 0x79);
        REQUIRE(!ex.cpu.registers.P.v);

        ex.instructionStep();               // ADC #$76
        // A should now be 0xEF, with overflow
        REQUIRE(ex.cpu.registers.A == 0xEF);
        REQUIRE(ex.cpu.registers.P.v);

        ex.instructionStep();               // ADC #$F5
        // A should now be 0xE4, no overflow
        REQUIRE(ex.cpu.registers.A == 0xE4);
        REQUIRE(!ex.cpu.registers.P.v);

        ex.instructionStep();               // ADC #$25 (and carry from previous ADC)
        // A should now be 0x0A, no overflow
        REQUIRE(ex.cpu.registers.A == 0x0A);
        REQUIRE(!ex.cpu.registers.P.v);
    }

    SECTION("Negative flag")
    {
        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x19,           // Load       0x19      into A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x60,           // Add        0x60      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x76,           // Add        0x76      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0xF5,           // Add        0xF5      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x25,           // Add        0x25      to   A  (2 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$19

        ex.instructionStep();               // ADC #$60
        // A should now be 0x79, not negative
        REQUIRE(ex.cpu.registers.A == 0x79);
        REQUIRE(!ex.cpu.registers.P.n);

        ex.instructionStep();               // ADC #$76
        // A should now be 0xEF, negative
        REQUIRE(ex.cpu.registers.A == 0xEF);
        REQUIRE(ex.cpu.registers.P.n);

        ex.instructionStep();               // ADC #$F5
        // A should now be 0xE4, negative
        REQUIRE(ex.cpu.registers.A == 0xE4);
        REQUIRE(ex.cpu.registers.P.n);

        ex.instructionStep();               // ADC #$25 (and carry from previous ADC)
        // A should now be 0x0A, not negative
        REQUIRE(ex.cpu.registers.A == 0x0A);
        REQUIRE(!ex.cpu.registers.P.n);
    }

    SECTION("Zero flag")
    {
        const std::vector<Byte> Program = {
            (Byte)Ins::LDA_IMM,         0x19,           // Load       0x19      into A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x60,           // Add        0x60      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x87,           // Add        0x87      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0xF5,           // Add        0xF5      to   A  (2 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDA #$19

        ex.instructionStep();               // ADC #$60
        // A should now be 0x79, non zero
        REQUIRE(ex.cpu.registers.A == 0x79);
        REQUIRE(!ex.cpu.registers.P.z);

        ex.instructionStep();               // ADC #$87
        // A should now be 0x00, zero
        REQUIRE(ex.cpu.registers.A == 0x00);
        REQUIRE(ex.cpu.registers.P.z);

        ex.instructionStep();               // ADC #$F5 (and carry from previous ADC)
        // A should now be 0xF6, non zero
        REQUIRE(ex.cpu.registers.A == 0xF6);
        REQUIRE(!ex.cpu.registers.P.z);
    }

    SECTION("Decimal carry")
    {
        const std::vector<Byte> Program = {
            (Byte)Ins::SED,                             // Set decimal flag
            (Byte)Ins::LDA_IMM,         0x11,           // Load       0x11      into A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x79,           // Add        0x79      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x76,           // Add        0x76      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x33,           // Add        0x33      to   A  (2 cycles)
            (Byte)Ins::ADC_IMM,         0x01,           // Add        0x01      to   A  (2 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // SED
        ex.instructionStep();               // LDA #$11

        ex.instructionStep();               // ADC #$79
        // A should now be 0x90, no carry
        REQUIRE(ex.cpu.registers.A == 0x90);
        REQUIRE(!ex.cpu.registers.P.c);

        ex.instructionStep();               // ADC #$76
        // A should now be 0x66, with carry
        REQUIRE(ex.cpu.registers.A == 0x66);
        REQUIRE(ex.cpu.registers.P.c);

        ex.instructionStep();               // ADC #$33 (and carry from previous ADC)
        // A should now be 0x00, with carry
        REQUIRE(ex.cpu.registers.A == 0x00);
        REQUIRE(ex.cpu.registers.P.c);

        ex.instructionStep();               // ADC #$01 (and carry from previous ADC)
        // A should now be 0x02, no carry
        REQUIRE(ex.cpu.registers.A == 0x02);
        REQUIRE(!ex.cpu.registers.P.c);
    }

    SECTION("Page cross (ADC a,X)")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ABS_X);

        const std::vector<Byte> Program = {
            (Byte)Ins::LDX_IMM,         0x20,           // Load       0x20      into X  (2 cycles)
            (Byte)Ins::LDA_IMM,         0x19,           // Load       0x19      into A  (2 cycles)
            (Byte)Ins::ADC_ABS_X,       0xFA,   0x01,   // Add     [0x01FA + X] to   A  (5 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // LDX #$20
        ex.instructionStep();               // LDA #$19
        uint64_t n = ex.instructionStep();  // ADC $01FA,X
        
        CHECK(n == it->second.minCycleCost + 1);
        // A should now be 0x1D
        REQUIRE(ex.cpu.registers.A == 0x1D);
    }

    SECTION("Page cross in decimal mode (ADC a,X)")
    {
        auto it = FIND_INSTRUCTION_INFO_OR_FAIL(Ins::ADC_ABS_X);

        const std::vector<Byte> Program = {
            (Byte)Ins::SED,                             // Set decimal flag             (2 cycles)
            (Byte)Ins::LDX_IMM,         0x20,           // Load       0x20      into X  (2 cycles)
            (Byte)Ins::LDA_IMM,         0x19,           // Load       0x19      into A  (2 cycles)
            (Byte)Ins::ADC_ABS_X,       0xFA,   0x01,   // Add     [0x01FA + X] to   A  (6 cycles)
        };

        ex.registerProgram(Program, StartAddress);
        ex.instructionStep();               // Reset sequence
        ex.instructionStep();               // SED
        ex.instructionStep();               // LDX #$20
        ex.instructionStep();               // LDA #$19
        uint64_t n = ex.instructionStep();  // ADC $01FA,X
        
        CHECK(n == it->second.maxCycleCost);
        // A should now be 0x23
        REQUIRE(ex.cpu.registers.A == 0x23);
    }
}

}
