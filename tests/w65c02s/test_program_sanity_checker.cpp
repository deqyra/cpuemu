#include <catch2/catch2.hpp>

#include <map>
#include <vector>

#include <common/types.hpp>
#include <w65c02s/program_sanity_checker.hpp>
#include <w65c02s/instruction.hpp>
#include <w65c02s/instruction_info.hpp>

#define TAGS "[w65c02s][utility]"

namespace emu::w65c02s
{

TEST_CASE("ProgramSanityChecker", TAGS)
{
    SECTION("Well-formed programs produce no errors")
    {
        const std::vector<Byte> Program = {
            (Byte)Instruction::LDA_IMM,      	0x02,		// Load 0x02 into A
            (Byte)Instruction::ADC_IMM,			0x03		// Add  0x03 to   A
        };

        std::map<uint64_t, SanityCheckError> errors = ProgramSanityChecker::CheckProgram(Program);
        REQUIRE(errors.empty());
    }

    SECTION("Unknown instructions are detected and reported as errors")
    {
        const std::vector<Byte> Program = {
            (Byte)Instruction::LDA_IMM,      	0x02,		// Load 0x02 into A
            (Byte)Instruction::ADC_IMM,			0x03,	    // Add  0x03 to   A
            0x03 // Any instruction whose lower nibble is 3 is invalid
        };

        std::map<uint64_t, SanityCheckError> errors = ProgramSanityChecker::CheckProgram(Program);
        CHECK(errors.size() == 1);
        auto it = errors.find(0x04);
        REQUIRE(it != errors.end());
        REQUIRE(it->second == SanityCheckError::UnknownInstruction);
    }
}

}
