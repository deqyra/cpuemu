#include <iostream>
#include <vector>

#ifdef _WIN32
    #include <windows.h>
#endif//_WIN32

#include <cpuemu/common/types.hpp>
#include <cpuemu/w65c02s/execution_wrapper.hpp>
#include <cpuemu/w65c02s/program_sanity_checker.hpp>

#include "main_tools.hpp"
#include "project_env.hpp"

int main(int argc, char** argv)
{
    #ifdef _WIN32
        SetConsoleOutputCP(65001);
    #endif

    std::cout << PROJECT_NAME << " v" << PROJECT_VERSION << '\n';
    std::cout << COPYRIGHT_NOTICE << '\n';
    std::cout << MIT_LICENSE_NOTICE << '\n' << std::endl;

    using namespace emu;
    using w65c02s::CPU;
    using Ins = w65c02s::Instruction;
    using w65c02s::ProgramSanityChecker;
    using w65c02s::SanityCheckError;
    using w65c02s::ExecutionWrapper;

    constexpr uint16_t StartAddress = 0x0000;
    const std::vector<Byte> Program = {
        (Byte)Ins::LDA_IMM,         0x02,       // Load 0x02 into A
        (Byte)Ins::ADC_IMM,         0x03        // Add  0x03 to   A
    };

    std::map<uint64_t, SanityCheckError> errors = ProgramSanityChecker::CheckProgram(Program);
    if (!errors.empty())
    {
        std::cout << "Program ill-formed, aborting..." << std::endl;
        return EXIT_FAILURE;
    }

    ExecutionWrapper ex;
    ex.registerProgram(Program, StartAddress);

    for (unsigned int i = 0; i < 11; i++)
    {
        ex.cycleStep();
    }

    return EXIT_SUCCESS;
}
