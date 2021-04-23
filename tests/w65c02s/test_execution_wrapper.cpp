#include <catch2/catch2.hpp>

#include <vector>

#include <common/types.hpp>
#include <w65c02s/execution_wrapper.hpp>
#include <w65c02s/instruction.hpp>
#include <w65c02s/instruction_info.hpp>

#define TAGS "[w65c02s][execute]"

namespace emu::w65c02s
{

TEST_CASE("ExecutionWrapper")
{
    using namespace emu;
    using Ins = w65c02s::Instruction;
    using w65c02s::ExecutionWrapper;

    constexpr uint16_t StartAddress = 0x0000;
    const std::vector<Byte> Program = {
        (Byte)Ins::LDA_IMM,         0x02,           // Load       0x02  into A  (2 cycles)
        (Byte)Ins::ADC_ABS,         0x00,   0x02,   // Add     [0x0200] to   A  (4 cycles)
        (Byte)Ins::ADC_IMM,         0x0F            // Add        0x0F  to   A  (2 cycles)
    };

    constexpr uint16_t DataAddress = 0x0200;
    const std::vector<Byte> Data = {
        0x03
    };

    ExecutionWrapper ex;
    ex.registerProgram(Program, StartAddress);
    ex.registerMemory(Data, DataAddress);

    // CPU now ready to start reset sequence

    SECTION("When amidst the reset sequence, the execution wrapper steps through to its end")
    {
        ex.cycleStep();             // First cycle of the reset sequence, 6 should remain
        uint64_t n = ex.instructionStep();
        REQUIRE(n == 6);
    }

    SECTION("The execution wrapper steps through an instruction and returns the correct number of cycle")
    {
        ex.instructionStep();       // Finish reset sequence
        
        ex.cycleStep();             // First cycle of LDA, 1 should remain
        uint64_t n = ex.instructionStep();
        CHECK(n == 1);

        ex.cycleStep();             // First cycle of ADC a, 3 should remain
        ex.cycleStep();             // Second   -   -   -    2  -       -
        n = ex.instructionStep();
        REQUIRE(n == 2);
    }

    SECTION("When a reset is requested amidst of an instruction, the execution wrapper steps through to its start")
    {
        ex.instructionStep();       // Finish reset sequence
        
        ex.cycleStep();             // First cycle of LDA, 1 should remain
        uint64_t n = ex.instructionStep();
        CHECK(n == 1);

        ex.cycleStep();             // First cycle of ADC a, 3 should remain
        ex.cpu.pins.resb = false;   // Request reset
        n = ex.instructionStep();   // Should stop at the start of the reset sequence, which is 2 cycles from now
        ex.cpu.pins.resb = true;    // Trigger reset
        CHECK(n == 2);

        // Processor should now be starting reset sequence, which lasts 7 cycles
        n = ex.instructionStep();
        REQUIRE(n == 7);
    }
}

}
