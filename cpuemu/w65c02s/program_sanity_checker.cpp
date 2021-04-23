#include "program_sanity_checker.hpp"

#include <functional>

#include "instruction.hpp"
#include "instruction_info.hpp"

namespace emu::w65c02s
{

std::map<uint64_t, SanityCheckError> ProgramSanityChecker::CheckProgram(const std::vector<Byte>& program)
{
    // std::vector<uint64_t> instructionLocations;
    // std::vector<uint64_t> referencedLocations;
    std::map<uint64_t, SanityCheckError> errors;

    uint64_t currentLocation = 0;
    while (currentLocation < program.size())
    {
        const Byte& instruction = program[currentLocation];

        // Check the current byte is an instruction
        auto it = InstructionInfoData.find((Instruction)instruction);
        if (it == InstructionInfoData.end())
        {
            errors[currentLocation] = SanityCheckError::UnknownInstruction;
            break;
        }

        // Todo: check jump/branch locations, ...

        // Next bytes are arguments to the instruction, skip them
        InstructionInfo info = it->second;
        currentLocation += info.instructionLength;
    }

    return errors;
}

}